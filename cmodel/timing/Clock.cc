#include "Clock.hh"

namespace Sim::Clock
{
    uint64_t m_tick = 0;

    uint64_t cur_tick()
    {
        return m_tick;
    }

    uint64_t tick()
    {
        return ++m_tick;
    }
}