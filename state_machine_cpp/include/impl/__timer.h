//
// Created by henri on 10/05/21.
//

#ifndef STATE_MACHINE_CPP___TIMER_H
#define STATE_MACHINE_CPP___TIMER_H

#include <chrono>

namespace state_machine_cpp {
    class Timer;
}

class state_machine_cpp::Timer {
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> time;
    bool m_has_started = false, m_has_stopped = false;
    time m_starting_clock;
    time m_ending_clock;
    double m_cumulative = 0;
public:
    void start();
    void stop();
    [[nodiscard]] double time_in_seconds() const;
    [[nodiscard]] double cumulative_time_in_seconds() const;
};

#endif //STATE_MACHINE_CPP___TIMER_H
