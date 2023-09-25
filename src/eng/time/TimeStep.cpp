#include "TimeStep.hpp"

TimeStep::TimeStep() :
    m_current_time{now()},
    m_accumulator{}
{
}

void TimeStep::tick()
{
    auto new_time = now();
    auto frame_time = new_time - m_current_time;
    m_current_time = new_time;
    m_accumulator += frame_time;
}

void TimeStep::advance()
{
    m_accumulator -= DELTA_TIME;
    m_t += DELTA_TIME;
    ++m_tick_count;
    if(m_tick_count == TICKS_TO_SECOND)
    {
        m_tick_count = 0;
    }
}

bool TimeStep::done() const
{
    return m_accumulator < DELTA_TIME;
}

TimeStep::delta_type TimeStep::delta_time()
{
    return std::chrono::duration_cast<std::chrono::duration<delta_type>>(DELTA_TIME).count();
}

TimeStep::time_type TimeStep::current_time() const
{
    return m_t;
}

TimeStep::time_type TimeStep::now() noexcept
{
    return clock_type::now();
}

bool TimeStep::second_passed() const noexcept
{
    return m_tick_count == 0;
}
