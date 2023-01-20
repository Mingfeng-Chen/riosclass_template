#include "InstructionCache.hh"

namespace Emulator
{

InstructionCache::InstructionCache(uint64_t Latency, Memory* memory)
    : TraceObject("InstructionCache"),
      m_Memory(memory)
{}

InstructionCache::~InstructionCache(){}

void 
InstructionCache::ReceiveFetchReq(MemReq_t mem,std::function<void(MemResp_t)> CallBackFunc){
    MemResp_t resp;
    resp.Id = mem.Id;
    resp.Address = mem.Address;
    resp.Opcode = mem.Opcode;
    resp.Length = mem.Length;
    resp.Data = NULL;
    this->m_Memory->read(mem.Address,&resp.Data,mem.Length);
    DPRINTF(InstructionCacheReq,"address {:#x}",mem_req.Address);
}

void 
InstructionCachePort::Reset(){
    this->m_InstructionCacheRespLatch.reset();
}   

void 
InstructionCachePort::Evaluate(){
    if(this->m_InstructionCacheRespLatch.OutPort->valid){
        this->m_InstructionCacheRespLatch.OutPort->data.first(this->m_InstructionCacheRespLatch.OutPort->data.second);
    }
}

void 
InstructionCachePort::Advance(){
    this->m_InstructionCacheRespLatch.advance();
}
    
} 