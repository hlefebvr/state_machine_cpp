//
// Created by henri on 10/05/21.
//

#include "impl/__timer.h"
#include <stdexcept>

void state_machine_cpp::Timer::start() {
    m_cumulative += time_in_seconds();
    m_starting_clock = std::chrono::high_resolution_clock::now();
    m_has_started = true;
    m_has_stopped = false;
}

void state_machine_cpp::Timer::stop() {
    if (m_has_stopped) {
        throw std::runtime_error("Timer has already been stopped.");
    }

    m_ending_clock = std::chrono::high_resolution_clock::now();
    m_has_stopped = true;
}

double state_machine_cpp::Timer::time_in_seconds() const {
    constexpr double convert_factor = 0.001;

    if (!m_has_started && !m_has_stopped) {
        return 0.0;
    }

    if (!m_has_stopped) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_starting_clock).count() * convert_factor;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(m_ending_clock - m_starting_clock).count() * convert_factor;
}

double state_machine_cpp::Timer::cumulative_time_in_seconds() const {
    return m_cumulative;
}
