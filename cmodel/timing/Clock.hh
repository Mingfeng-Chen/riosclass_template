#pragma once

#include <cstdint>

namespace Sim::Clock
{
    // Global tick variable
    extern uint64_t m_tick;

    /**
     * Get current tick
     * @return uint64_t current tick
     */
    extern uint64_t cur_tick();

    /**
     * Current tick increment
     * @return uint64_t current tick after incrementation
     */
    extern uint64_t tick();
}