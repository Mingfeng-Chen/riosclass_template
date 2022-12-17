#include "Memory.hpp"
#include "Processor.hpp"
#include "Bus.hpp"

class Simulation{
    private:
        Memory* memory;
        Processor* processor;
        Bus* bus;
        bool flag;
    
    public:
        Simulator();
        void SetRam(Memory* memory);
        void SetCPU(Processor* processor);
        void SetBus(Bus* bus);
        void Init();
        void Tick();
};