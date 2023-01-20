#include "Dispatch.hh"
#include "../processor/Processor.hh"
#include <math.h>
namespace Emulator
{
    
Dispatch::Dispatch(
    Processor* processor
):  BaseStage(processor,"Dispatch")
{
}

Dispatch::~Dispatch(){}


void 
Dispatch::AddSchedular(std::shared_ptr<BaseSchedular> Schedular){
    Disp_Schedular_t disp_scheduler_element;
    disp_scheduler_element.scheduler = Schedular;
    disp_scheduler_element.AvailPort = Schedular->m_EnqueWidth;
    this->m_SchedularVec.emplace_back(disp_scheduler_element);
}

void 
Dispatch::Reset(){}

void 
Dispatch::Evaluate(){

    std::shared_ptr<Rcu> rcu  = this->m_Processor->getRcuPtr();
    std::shared_ptr<Lsq> lsq  = this->m_Processor->getLsqPtr();
    InsnPkg_t& insnPkg        = this->m_StageInPort->data;

    uint64_t TryAllocSuccessCount[3];

    StageAck_t  Ack = {0};

    DASSERT((insnPkg.size()<=rcu->m_AllocWidth),
        "Dispatch[{}] & RCU Allocate[{}] Width MisMatch!",insnPkg.size(),rcu->m_AllocWidth
    );

    if(this->m_StageInPort->valid){
        if(rcu->m_RobState != rob_state_t::Rob_Idle){
            this->m_StageInPort->stall();
        }else{
            if(m_MustTakenAllInsn){
                rcu->TryAllocate(insnPkg,TryAllocSuccessCount[0]);
                lsq->TryAllocate(insnPkg,TryAllocSuccessCount[1]);
                this->TryDispatch(insnPkg,TryAllocSuccessCount[2]);
                if(*std::min_element(TryAllocSuccessCount,TryAllocSuccessCount+3) < insnPkg.size()){
                    this->m_StageInPort->stall();
                }else{
                    lsq->Allocate(insnPkg,insnPkg.size());
                    rcu->Allocate(insnPkg,insnPkg.size());
                    this->DispatchInsn(insnPkg,insnPkg.size());
                    Ack.takenInsnCount = insnPkg.size();
                    this->m_StageAckOutPort->set(Ack);
                }
            }else{
                lsq->TryAllocate(insnPkg,TryAllocSuccessCount[1]);
                rcu->TryAllocate(insnPkg,TryAllocSuccessCount[0]);
                this->TryDispatch(insnPkg,TryAllocSuccessCount[2],true);
                Ack.takenInsnCount = *std::min_element(TryAllocSuccessCount,TryAllocSuccessCount+3);
                lsq->Allocate(insnPkg,Ack.takenInsnCount);
                rcu->Allocate(insnPkg,Ack.takenInsnCount);
                this->DispatchInsn(insnPkg,Ack.takenInsnCount);

                this->m_StageAckOutPort->set(Ack);
            }
            #ifdef TRACE_ON
            std::stringstream insnInfo;
            if(Ack.takenInsnCount){
                for(size_t i = 0; i < Ack.takenInsnCount; i++){
                    auto t = this->m_StageInPort->data[i];
                    insnInfo << fmt::format("\n\tInsn_{:02} -> Pc({:#x}) , Insn({:#>08x})",i, t->Pc, t->CompressedInsn);
                }
                DPRINTF(SendReq,insnInfo.str());
            }
            #endif
        }
    }
}

void 
Dispatch::TryDispatch(InsnPkg_t& insnPkg, uint64_t& SuccessCount, bool CheckControlFlow){
    // Flush Status
    for(auto& scheduler : this->m_SchedularVec){
        scheduler.AvailPort = std::min(scheduler.scheduler->GetAvailibleEntryCount(),scheduler.scheduler->m_EnqueWidth);
    }

    SuccessCount = 0;
    for(auto& insn : insnPkg){

        if(insn->Excp.valid){
            SuccessCount++;
            break;
        }
        if((insn->Fu == funcType_t::ALU && insn->IsaRd == 0)){ // NOP
            SuccessCount++;  
            continue;
        }
        bool Success = false;
        for(auto& schedular : this->m_SchedularVec){
            if(schedular.scheduler->m_SupportFunc.count(insn->Fu) && !schedular.scheduler->Busy() && 
                schedular.AvailPort)
            {
                SuccessCount++;
                schedular.AvailPort--;
                Success = true;
                break;
            }
        }
        if(!Success || (CheckControlFlow && insn->ControlFlowInsn)){
            break;
        }
    }
}

void 
Dispatch::DispatchInsn(InsnPkg_t& insnPkg, uint64_t DispatchCount){
    for(size_t i = 0 ; i < DispatchCount; i++){
        InsnPtr_t insn = insnPkg[i];
        if(  insn->Excp.valid ||
             ((insn->Fu == funcType_t::CSR) && (insn->SubOp == CSR_FENCE)) ||
             ((insn->Fu == funcType_t::ALU) && (insn->IsaRd == 0)) ||
             ((insn->Fu == funcType_t::CSR) && (insn->SubOp == CSR_MRET))
        ){
            insn->State = InsnState_t::State_Commit;
        }else{
            bool Success = false;
            for(auto scheduler : this->m_SchedularVec){
                if(scheduler.scheduler->m_SupportFunc.count(insn->Fu) && !scheduler.scheduler->Busy())
                {
                    scheduler.scheduler->Schedule(insn,scheduler.scheduler->Allocate());
                    Success = true;
                    break;
                }
            } 
            DASSERT(Success,"Unexpected Dispatch Fail!")
        }
    }
}

std::shared_ptr<BaseStage> Create_Dispatch_Instance(
        Processor*                       processor         ,
        const YAML::Node&                StageConfig    
){
    const YAML::Node& SchedularInfo = StageConfig["Schedulers"];
    auto t = std::make_shared<Dispatch>(processor);
    for(size_t i = 0 ; i < SchedularInfo.size(); i++){
        const uint16_t SchedularId = SchedularInfo[i].as<uint16_t>();
        t->AddSchedular(processor->m_SchedularVec[SchedularId]);
    }
    return t;
}



} // namespace Emualtor