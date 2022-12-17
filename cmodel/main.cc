#include "Memory.hh"
#include "Processor.hh"
#include "Simulation.hh"
#include "Bus.hh"
#include "fstream"

int main(){
    memory=LoadHex("hex/add.hex")
    processor=new Processor;
    bus=new Bus;
    Simulation sim;
    sim.SetBus(bus);
    sim.SetMemory(memory);
    sim.SetProcessor(processor);
    sim.Init();
    for(int i=0;i<maxCycle;i++){
        sim.Tick();
    }
    return 0;
}

Memory* LoadHex(string path) {
    Memory* memory=new Memory(0x80000000);
    LoadHexToRAM(path, memory);
    return memory;
}
