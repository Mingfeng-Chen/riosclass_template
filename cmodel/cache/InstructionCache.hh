#ifndef __INSTRUCTIONCACHE_HH__
#define __INSTRUCTIONCACHE_HH__ 

#include "../Memory/Memory.hh"



namespace Emulator
{
class InstructionCache : public Trace::TraceObject
{
private:

    Memory*              m_Memory;

    TimeBuffer<std::pair<std::function<void(MemResp_t)>,MemResp_t>>  m_iCacheRespLatch;
    
public:
    
    InstructionCache();
    
    InstructionCache(uint64_t Latency , Memory* memory);
    
    ~InstructionCache();

    void ReceiveFetchReq(MemReq_t mem, std::function<void(MemResp_t)> CallBackfunc);

    void Reset();

    void Evaluate();

    void Advance();

};


} // namespace Emulator




#endif	