#include <utility>

#include "Processor.hh"
#include "pipeline/Fetch1.hh"

namespace Sim::Processor
{
// Use this to register Processor with name "Processor"
    Factory::BaseFactory<id_t, Memory::BaseDramPtr>::Register<Processor> ProcessorRegistry("Processor");

    Processor::Processor(const Config::JsonConfig &config, id_t id, Memory::BaseDramPtr dram)
            : SimObject(fmt::format("Processor {:02d}", id)), m_dram(std::move(dram))
    {
        tid = id;
        xlen = config["xlen"];

        for (auto &cfg: config["stages"])
        {
            m_stages.push_back(std::dynamic_pointer_cast<Pipeline::BaseStage>(
                    Factory::BaseFactory<Processor &>::instance().newComponent(cfg["type"], cfg, *this)
            ));
        }

        logger->info("Initiated Processor {:02d}", id);
    }

    void Processor::reset()
    {
        reset(0x00000000);
    }

    void Processor::reset(Addr addr)
    {
        logger->info("{} reset to start at {:#010x}", name, addr);
        for (const auto& stg: m_stages)
        {
            stg->reset();
        }
        std::dynamic_pointer_cast<Pipeline::Fetch1>(m_stages[0])->set_addr(addr);
    }

    void Processor::tick()
    {
        evaluate();
        advance();
    }

    void Processor::advance()
    {
        //
    }

    void Processor::evaluate()
    {
        for (const auto& stg: m_stages)
        {
            stg->evaluate();
        }
    }
} // namespace Sim::Processor