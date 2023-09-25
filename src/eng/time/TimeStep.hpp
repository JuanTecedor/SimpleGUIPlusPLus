#ifndef TIME_STEP_HPP
#define TIME_STEP_HPP

#include <chrono>

class TimeStep
{
public:
    using delta_type = float;
    using clock_type = std::chrono::high_resolution_clock;
    using time_type = std::chrono::time_point<clock_type>;

    TimeStep();
    void tick();
    void advance();
    [[nodiscard]] bool done() const;
    [[nodiscard]] static delta_type delta_time();
    [[nodiscard]] time_type current_time() const;
    [[nodiscard]] bool second_passed() const noexcept;
private:
    using resolution_type = std::chrono::milliseconds;
    using duration_type = std::chrono::duration<delta_type>;

    time_type m_t;
    time_type m_current_time;

    duration_type m_accumulator;
    constexpr static auto DELTA_TIME = resolution_type(10);
    constexpr static auto TICKS_TO_SECOND = std::chrono::seconds(1) / DELTA_TIME;
    int m_tick_count = 0;  // Resets to 0 every TICKS_TO_SECOND

    [[nodiscard]] static time_type now() noexcept;
};

#endif
