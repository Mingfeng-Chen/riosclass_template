#include "Fetch.hh"
#include "../Processor.hh"

namespace Emulator
{
    
Fetch::Fetch( 
    Processor*          processor            ,
    const   uint64_t    InstrBufferSize      
    
) : BaseStage(processor,"Fetch"),
    m_InsnBuffer("InsnBuffer",InstrBufferSize)
{}

Fetch::~Fetch(){}
    
void 
Fetch::Evaluate(){
    this->ReleaseAction();

    this->ReceiveReq();
    this->SendReq();
}    

void 
Fetch::Reset(){
    this->m_FlushSyncLatch.reset();
    this->m_InsnBuffer.Reset();
}    

void 
Fetch::FlushAction(){
    this->m_InsnBuffer.Reset();
}

void
Fetch::ReleaseAction(){
    if(this->m_StageAckInPort->valid){
        for(size_t i = 0; i < this->m_StageAckInPort->data.takenInsnCount ; i++){
            this->m_InsnBuffer.Pop();
        }
    }
}

void 
Fetch::ReceiveReq(){
    if(this->m_StageInPort->valid){
        DASSERT((this->m_InsnBuffer.getSize() >= this->m_FromLastStageInsnCount), "Can Never Taken All Insn");
        if(this->m_InsnBuffer.getAvailEntryCount() >= this->m_FromLastStageInsnCount){
            InsnPkg_t insnPkg = this->m_StageInPort->data;
            for(auto insn : insnPkg){
                if(insn){
                    insn->State = InsnState_t::State_Fetch;
                    this->m_InsnBuffer.Push(insn);            
                }
            }
            #ifdef TRACE_ON
            std::stringstream insnInfo;
            for(size_t i = 0; i < insnPkg.size(); i++){
                if(auto t = insnPkg[i]){
                    insnInfo << fmt::format("\n\tInsn_{:02} -> Pc({:#x}) , Insn({:#>08x})",i, t->Pc, t->CompressedInsn);
                }else{
                    break;
                }
            }
            DPRINTF(ReceiveReq,insnInfo.str());
            #endif
        } 
        else{
            Redirect_t replayReq;
            replayReq.target = this->m_StageInPort->data.front()->Pc;
            replayReq.StageId = InsnState_t::State_Fetch;
            this->m_Processor->FlushBackWard(InsnState_t::State_Fetch);
            this->m_RedirectPort->set(replayReq);
            DPRINTF(Replay,"InsnBuffer Full, Replay Fetch {:#x}",replayReq.target);
        }
    }
}

void 
Fetch::SendReq(){
    if(!this->m_InsnBuffer.empty() && !this->m_StageOutPort->isStalled()){
        InsnPkg_t insnPkg;
        uint64_t  ibPtr = this->m_InsnBuffer.getHeader();
        for(size_t i = 0 ; (i < this->m_ToNextStageInsnCount) &&
                           (i < this->m_InsnBuffer.getUsage()); i++)
        {
            insnPkg.emplace_back(this->m_InsnBuffer[ibPtr]);
            ibPtr = this->m_InsnBuffer.getNextPtr(ibPtr);
        }
        this->m_StageOutPort->set(insnPkg);
    }
}

std::shared_ptr<BaseStage> Create_Fetch_Instance(
        Processor*                       processor         ,
        const YAML::Node&                StageConfig    
){
    const uint64_t InstrBufferSize      = StageConfig["InstrBufferSize"].as<uint64_t>() ;
    return std::shared_ptr<BaseStage>(
        new Fetch(processor,InstrBufferSize)
    );  
}
} // namespace Emulator
