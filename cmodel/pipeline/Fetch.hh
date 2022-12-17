#ifndef __Fetch_HH__
#define __Fetch_HH__ 


#include "BaseStage.hh"
#include "Pipe_data.hh"
#include "../Component/LoopQueue.hh"

#include "../../Common/Common.hh"

namespace Emulator
{
    
class Fetch : public BaseStage
{
private:

    LoopQueue<InsnPtr_t>    m_InsnBuffer;

public:
    Fetch( Processor*          processor            ,
            const   uint64_t    InstrBufferSize      
    );

    ~Fetch();
    
    void Evaluate();     
    
    void Reset();       
    
    void ReleaseAction();

    void FlushAction();

    void ReceiveReq();

    void SendReq();
};

std::shared_ptr<BaseStage> Create_Fetch_Instance(
        Processor*                       processor         ,
        const YAML::Node&                StageConfig    
);  

} // namespace Emulator


#endif	