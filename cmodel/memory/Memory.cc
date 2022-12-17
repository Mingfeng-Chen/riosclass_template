#include "cstdint"

#include "Memory.hh"

namespace Sim::Memory
{
    Factory::BaseFactory<>::Register<Memory> MemoryRegistry("Memory");

    Memory::Memory(const Config::JsonConfig &cfg) : SimObject("Memory")
    {
        m_base = cfg["base"];
        m_length = cfg["length"];

        /* Reserve Memory space */
        m_raw_mem = new u_char[m_length];
        m_io_mem = new u_char[m_base - m_io_base];
        m_hole_mem = new u_char[m_hole_end - m_base - m_length];
    }

    Memory::~Memory()
    {
        delete m_raw_mem;
        delete m_io_mem;
        delete m_hole_mem;
    }

    inline bool Memory::checkRange(Addr addr, Addr length) const
    {
        return (addr >= m_base) && (addr + length < m_base + m_length);
    }

        void Memory::write(const u_char *data, Addr addr, Addr length)
    {
        do_assert(checkRange(addr, length - 1), "Access out of range address : {:#x} -> {:#x}", addr, addr + length - 1);
        std::memcpy(m_raw_mem + addr - m_base, data, length);
    }

    void Memory::write(const u_char *data, Addr addr, Addr length, Addr mask)
    {
        do_assert(checkRange(addr, length - 1), "Access out of range address : {:#x} -> {:#x}", addr, addr + length - 1);
        for (size_t i = 0; i < length; ++i)
        {
            if ((mask >> i) & 1) m_raw_mem[addr - m_base + i] = data[i];
        }
    }

    void Memory::writeByte(u_char data, Addr addr)
    {
        do_assert(checkRange(addr, 0), "Access out of range address : {:#x}", addr);
        m_raw_mem[addr] = data;
    }

    void Memory::writeDouble(uint64_t data, Addr addr)
    {
        do_assert(checkRange(addr, 7), "Access out of range address : {:#x}", addr);
        std::memcpy(m_raw_mem + addr - m_base, (u_char *) (&data), 8);
    }

    u_char *Memory::read(u_char *dest, Addr addr, Addr length)
    {
        do_assert(checkRange(addr, length - 1), "Access out of range address : {:#x}:{:#x}", addr, addr + length - 1);
        std::memcpy(dest, m_raw_mem + addr - m_base, length);
        return dest;
    }

    u_char Memory::readByte(Addr addr)
    {
        do_assert(checkRange(addr, 0), "Access out of range address : {:#x}", addr);
        return m_raw_mem[addr - m_base];
    }

    uint64_t Memory::readDouble(Addr addr)
    {
        do_assert(checkRange(addr, 7), "Access out of range address : {:#x}", addr);
        return *(u_int64_t *) (m_raw_mem + addr - m_base);
    }

}
