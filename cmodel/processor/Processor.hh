#pragma once

#include "common/common.hh"
#include "SimObject.hh"
#include "Factory.hh"

#include "memory/Memory.hh"
#include "timing/TimeBuffer.hh"
#include "pipeline/BaseStage.hh"

#include "DynInst.hh"

namespace Sim::Processor
{
    namespace Pipeline
    {
        class BaseStage;

        typedef std::shared_ptr<BaseStage> BaseStagePtr;
    }
    /**
     * @brief Processor class
     */
    class Processor : public SimObject
    {
    public:
        // Local thread ID
        ThreadId tid;

        // Arch X-Length
        Xlen xlen;

    protected:

        // Pointer to DRAM, maybe used to direct access, timing access or assigned to submodules
        Memory::BaseDramPtr m_dram;

        std::vector<Pipeline::BaseStagePtr> m_stages;

    public:
        /**
         * @brief Constructor of Processor
         *
         * @param config
         * @param id
         */
        Processor(const Config::JsonConfig &config, id_t id, Memory::BaseDramPtr);

        ~Processor() override = default;

        void reset() override;

        /**
         * @brief Reset CPU to start at Addr
         * @param addr running start address
         */
        void reset(Addr addr);

        void tick() override;

        void advance() override;

        void evaluate() override;
    };

    typedef std::shared_ptr<Processor> CPUPtr;
}
