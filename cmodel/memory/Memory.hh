#pragma once

#include "common/common.hh"
#include "common/types.hh"
#include "SimObject.hh"
#include "Factory.hh"

namespace Sim::Memory
{
    /**
     * @brief Base DRAM class
     */
    class Memory : public Sim::SimObject
    {
    protected:
        /* base address of dram */
        Addr m_base = 0x0;

        /* length of dram */
        Addr m_length = 0x0;

        /* base address of io memory */
        Addr m_io_base = 0x0;

        /* Highest memory address */
        Addr m_hole_end = 0xffffffff;

        /* DRAM raw data */
        u_char *m_raw_mem;

        /* IO memory range */
        u_char *m_io_mem;

        /* Other memory  */
        u_char *m_hole_mem;

    public:
        /**
         * @brief Construct a new Memory object
         *
         */
        Memory() : SimObject("Memory")
        {
            m_raw_mem = m_io_mem = m_hole_mem = nullptr;
        }

        /**
         * @brief Construct a new Memory object according to config
         * 
         * @param cfg
         */
        explicit Memory(const Config::JsonConfig &config);

        ~Memory() override;

        /**
         * @brief SimObject Interface function, unimplemented.
         */
        void reset() override
        {}

        /**
         * @brief SimObject Interface function, unimplemented.
         */
        void tick() override
        {}

        /**
         * @brief SimObject Interface function, unimplemented.
        */
        void evaluate() override
        {}

        /**
         * @brief SimObject Interface function, unimplemented.
        */
        void advance() override
        {}

        /**
         * @brief check the given address & length is in range of memory
         * @param addr
         * @param length
         * @return
         */
        [[nodiscard]] inline bool checkRange(Addr addr, Addr length = 0) const;

        /**
         * @brief Put data of memory from addr to addr + length to dest
         * @param addr
         * @param length
         * @return
         */
        u_char *read(u_char *dest, Addr addr, Addr length);

        /**
         * Read a single byte and return
         * @param addr
         * @return
         */
        u_char readByte(Addr addr);

        /**
         * @brief Read double word (8 bytes) and return
         * @param addr
         * @return
         */
        uint64_t readDouble(Addr addr);

        /**
         * put data into raw memory at addr to addr + length
         * @param data
         * @param addr
         * @param length
         */
        void write(const u_char *data, Addr addr, Addr length);

        /**
         * @brief put data into raw memory at addr to addr + length but mask some byte
         * @param data
         * @param addr
         * @param length
         * @param mask
         */
        void write(const u_char *data, Addr addr, Addr length, Addr mask);

        /**
         * @brief put a byte data into raw memory at addr
         * @param data
         * @param addr
         */
        void writeByte(u_char data, Addr addr);

        /**
         * @brief put double word (8 bytes) data into raw memory at addr
         * @param data
         * @param addr
         */
        void writeDouble(uint64_t data, Addr addr);
    };

    typedef std::shared_ptr<Memory> MemoryPtr;
}