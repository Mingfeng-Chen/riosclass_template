#include "StageFactory.hh"
#include "Pipeline/Fetch.hh"
#include "Pipeline/Decode.hh"
namespace Emulator
{

namespace StageFactory{

const std::map<std::string,createfunc> m_createFuncMap = {
    {"Fetch",Create_Fetch_Instance},
    {"Decode",Create_Decode_Instance},
};

const std::map<std::string,InsnState_t> m_StageEnumMap = {
    {"Fetch"   ,State_Fetch},
    {"Decode"   ,State_Decode},
};

std::shared_ptr<BaseStage> 
CreateStageByName(const std::string Name, Processor* p, const YAML::Node& config){
    std::map<std::string,createfunc>::const_iterator it = m_createFuncMap.find(Name);
    if(it != m_createFuncMap.end()){
        return it->second(p,config);
    }else{
        SPDLOG_ERROR("Unknown Stage {} !",Name);
        exit(-1);
    }
}

const InsnState_t
LookupEnumByName(std::string Name){
    std::map<std::string,InsnState_t>::const_iterator it = m_StageEnumMap.find(Name);
    if(it != m_StageEnumMap.end()){
        return it->second;
    }else{
        SPDLOG_ERROR("Unknown Stage {} !",Name);
        exit(-1);
    }
}

}
} 