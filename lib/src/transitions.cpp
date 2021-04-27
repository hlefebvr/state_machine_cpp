//
// Created by henri on 22/04/21.
//

#include <cassert>
#include <iostream>
#include "transitions.h"


state_machine_cpp::Transition::Any::Any(const State::Instance &t_initial_state) : m_initial_state(t_initial_state) {

}

const state_machine_cpp::State::Instance &state_machine_cpp::Transition::Any::operator()(Context &t_context) const {
    assert(bool(m_function));
    int result = m_function(t_context);
    assert(result < m_next_states.size());
    return m_next_states[result];
}

bool state_machine_cpp::Transition::Any::has_handler() const {
    return bool(m_function);
}

std::vector<state_machine_cpp::State::Instance> state_machine_cpp::Transition::Any::next_states() const {
    return m_next_states;
}

void state_machine_cpp::Transition::Any::reset_handler() {
    m_function = std::function<int(Context&)>();
    m_next_states.clear();
}

void
state_machine_cpp::Transition::Any::set_handler(std::vector<State::Instance> &&t_next_states, std::function<int(Context &)> &&t_handler) {
    m_next_states = std::move(t_next_states);
    m_function = std::move(t_handler);
}

void state_machine_cpp::Transition::Any::set_as_final() {
    m_is_final = true;
}

bool state_machine_cpp::Transition::Any::is_final() const {
    return m_is_final;
}
