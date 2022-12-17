#include "Simulation.hh"

Simulator::Simulator() {
    this->memory=nullptr;
    this->processor=nullptr;
    flag=true;
}

void Simulation::SetMemory(Memory* memory){
    this->memory=memory;
}
void Simulation::SetProcessor(Processor* processor){
    this->processor=processor;
}
void Simulation::Init(){
    this->bus->Init(this->memory);
    this->processor->BindBus(this->bus);
}
void Simulation::Tick(){
    if(flag){
        this->processor->GenPC();
        this->processor->Fetch();
        this->processor->Decode();
    }else{
        this->processor->Fetch();
        this->processor->Decode();
    }
}