#pragma once

#include <utility>
#include <functional>

#include "common/common.hh"

#include "SimObject.hh"
#include "Processor/BaseProcessor.hh"
#include "timing/TimeBuffer.hh"

#include "PipelineData.hh"

namespace Sim::Processor
{
    class Processor;

    namespace Pipeline
    {
        /**
         * Base Stage class derived from SimObject, containing ref to Processor
         */
        class BaseStage : public SimObject
        {
        protected:
            // ID same with Processor thread id
            id_t id;

            // ref to the owner Processor
            BaseProcessor &m_Processor;

            // Stage Inst input port
            std::shared_ptr<Timing::TimeBuffer<InstPkg>::BasePort> m_stage_in = nullptr;

            // Stage Inst output port
            std::shared_ptr<Timing::TimeBuffer<InstPkg>::BasePort> m_stage_out = nullptr;

            // Stage Acknowledge input port
            std::shared_ptr<Timing::TimeBuffer<StageAck>::BasePort> m_stage_ack_in = nullptr;

            // Stage Acknowledge output port
            std::shared_ptr<Timing::TimeBuffer<StageAck>::BasePort> m_stage_ack_out = nullptr;

            // Stage Redirect input port
            std::shared_ptr<Timing::TimeBuffer<Redirect>::BasePort> m_redirect = nullptr;

            // Stage flush sync latch
            Timing::TimeBuffer<bool> m_flush_sync_latch;

        public:
            /**
             * BaseStage constructor
             * @param name module name
             * @param id Processor thread id
             * @param Processor ref to owner Processor
             */
            BaseStage(std::string name, BaseProcessor &Processor);

            /**
             * Default deconstruct function
             */
            ~BaseStage() override = default;

            /**
             * @brief virtual advancing function, advance flush latch & check flush signal
             */
            void advance() override;

            virtual void release_action()
            {}

            virtual void flush()
            {}

            virtual void flush_action()
            {}

            /**
             * @brief connect stage input port to this stage
             * @param stage_in ref pointer to a BasePort
             */
            void connect_in_port(const std::shared_ptr<Timing::TimeBuffer<InstPkg>::BasePort> &stage_in);

            /**
             * @brief connect stage output port to this stage
             * @param stage_out ref pointer to a BasePort
             */
            void connect_out_port(const std::shared_ptr<Timing::TimeBuffer<InstPkg>::BasePort> &stage_out);

            /**
             * @brief connect stage ack input port to this stage
             * @param stage_ack_in ref pointer to a BasePort
             */
            void connect_ack_in_port(const std::shared_ptr<Timing::TimeBuffer<StageAck>::BasePort> &stage_ack_in);

            /**
             * @brief connect stage ack output port to this stage
             * @param stage_ack_out ref pointer to a BasePort
             */
            void connect_ack_out_port(const std::shared_ptr<Timing::TimeBuffer<StageAck>::BasePort> &stage_ack_out);

            /**
             * @brief connect redirect port to this stage
             * @param redirect ref pointer to a BasePort
             */
            void connect_redirect_port(const std::shared_ptr<Timing::TimeBuffer<Redirect>::BasePort> &redirect);
        };

        typedef std::shared_ptr<BaseStage> BaseStagePtr;
    }
}
