#ifndef __DATACACHE_HH__
#define __DATACACHE_HH__

#include "../memory/Memory.hh"

namespace Emulator
{
    class BaseCLINT;

    class DataCache : public Trace::TraceObject
    {
    private:
        Memory* m_memory;
        BaseCLINT* m_baseCLINT;

        TimeBuffer<std::pair<std::function<void(MemResp_t)>, MemResp_t>> m_dCacheRespLatch;

    public:
        DataCache(uint64_t Latency, Memory* memory);
        DataCache(uint64_t Latency, Memory* memory, BaseCLINT* clint);

        ~DataCache();

        void ReceiveMemReq(MemReq_t mem_req, std::function<void(MemResp_t)> CallBackfunc);

        MemResp_t ReceivePTWReq(MemReq_t mem_req, std::function<void(MemResp_t)> CallBackfunc, uint64_t& _pteBits);

        void Reset();

        void Evaluate();

        void Advance();

        bool ReservationValidGet(Addr_t addr);

        bool ReservationValidSet(Addr_t addr, bool valid);

        void AmoOpCal(MemReq_t& mem_req, char* storeVal, uint64_t& op1, uint64_t& op2);
        bool AmoIsSc(InsnPtr_t insn);
    };

} // namespace Emulator

#endif