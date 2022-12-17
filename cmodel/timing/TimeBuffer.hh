#pragma once

#include <queue>
#include <utility>

#include "common/common.hh"
#include "SimObject.hh"

namespace Sim::Timing
{
    /**
     * @brief Time buffer class, containing pointer to 2 ports and a queue of data
     * @tparam T
     */
    template<typename T>
    class TimeBuffer : public SimObject
    {
    public:
        /**
         * @brief Base port class, providing data access to time buffer
         */
        class BasePort
        {
        protected:
            // flag to indicate if the port & buffer is stalled
            std::shared_ptr<bool> m_stall;

            // flag to indicate if the port & buffer is being flushed
            std::shared_ptr<bool> m_flush;

            // Hold the data
            T data;

        public:
            // Flag of if the port is valid
            bool valid = false;

        public:
            /**
             * @brief Constructor of BasePort, called by TimeBuffer constructor
             * @param stall_sig
             * @param flush_sig
             */
            BasePort(std::shared_ptr<bool> stall_sig, std::shared_ptr<bool> flush_sig)
                    : m_stall(std::move(stall_sig)), m_flush(std::move(flush_sig))
            {}

            /**
             * @brief default deconstruct func
             */
            ~BasePort() = default;

            /**
             * @brief assign data to a port
             * @param _data
             */
            void set_data(T _data)
            {
                valid = true;
                data = _data;
            }

            /**
             * @brief Return the data hold in port
             * @return T data
             */
            inline T get_data()
            {
                return data;
            }

            /**
             * @brief Invalid the port by setting valid to false
             */
            void invalid()
            {
                valid = false;
            }

            /**
             * @brief Stall the port & all time buffer
             */
            void stall()
            {
                *m_stall = true;
            }

            /**
             * @brief Signal to flush the buffer and port
             */
            void flush()
            {
                *m_flush = true;
            }

            /**
             * @brief get the status of this port & buffer is stalled or not
             * @return bool
             */
            inline bool is_stalled()
            {
                return *m_stall;
            }
        };

    protected:

        /**
         * @brief Entry in the queue of time buffer
         */
        struct TimeBufferEntry
        {
            // hold data
            T data;

            // E.T.A of this data
            uint64_t dest_tick;
        };

        typedef std::queue<TimeBufferEntry> TimeBufferQueue;

        // buffer queuing data
        TimeBufferQueue m_queue;

        // latency of transferring data
        const Latency m_latency;

        // shared flag of buffer stalled
        std::shared_ptr<bool> m_stall;

        // shared flag of buffer being flushed
        std::shared_ptr<bool> m_flush;

        // BasePortPtr for input to this buffer
        std::shared_ptr<BasePort> m_in_port;

        // BasePortPtr for output from this buffer
        std::shared_ptr<BasePort> m_out_port;

    public:
        /**
         * @brief Constructor of TimeBuffer, ports are created along with it.
         * @param name
         * @param latency
         */
        TimeBuffer(std::string name, Latency latency)
                : SimObject(name), m_latency(latency)
        {
            m_stall = std::make_shared<bool>(false);
            m_flush = std::make_shared<bool>(false);

            m_in_port = std::make_shared<BasePort>(m_stall, m_flush);

            if (latency == 0)
            {
                m_out_port = m_in_port;
            }
            else
            {
                m_out_port = std::make_shared<BasePort>(m_stall, m_flush);
            }
        }

        /**
         * @brief stall this whole buffer
         */
        void stall()
        {
            *m_stall = true;
        }

        /**
         * @brief signal to flush this buffer
         */
        void flush()
        {
            *m_flush = true;
        }

        /**
         * tell if this buffer being flushed
         * @return bool
         */
        inline bool is_flushing()
        {
            return *m_flush;
        }

        /**
         * tell if this buffer stalled
         * @return bool
         */
        inline bool is_stalled()
        {
            return *m_stall;
        }

        /**
         * tell if this buffer flushed and drained
         * @return bool
         */
        inline bool is_drained()
        {
            return m_queue.empty();
        }

        /**
         * @brief reset this buffer, this will clear queue
         */
        void reset() override
        {
            *m_stall = false;
            *m_flush = false;

            m_out_port->invalid();
            m_in_port->invalid();

            while (!m_queue.empty())
                m_queue.pop();
        }

        /**
         * @brief SimObject interface function, unimplemented
         */
        void tick() override
        {}

        /**
         * @brief Advance this buffer, receive new data from in-port, put available data into out-port.
         */
        void advance() override
        {
            if (!is_flushing())
            {
                if (!is_stalled())
                {
                    if (m_latency && m_in_port->valid)
                    {
                        m_queue.push({m_in_port->get_data(), Clock::cur_tick() + m_latency - 1});
                        m_in_port->invalid();
                    }
                    m_out_port->invalid();
                    if (m_latency && !m_queue.empty() && m_queue.front().dest_tick <= Clock::cur_tick())
                    {
                        m_out_port->set_data(m_queue.front().data);
                        m_queue.pop();
                    }
                }
                else
                {
                    *m_stall = true;
                }
            }
            else
            {
                reset();
            }
        }

        /**
         * @brief SimObject interface function, unimplemented
         */
        void evaluate() override
        {}

        /**
         * @brief get the input port
         * @return pointer to input port
         */
        const std::shared_ptr<BasePort> &get_in_port() const
        {
            return m_in_port;
        }

        /**
         * @brief get the output port
         * @return pointer to output port
         */
        const std::shared_ptr<BasePort> &get_out_port() const
        {
            return m_out_port;
        }
    };
}
