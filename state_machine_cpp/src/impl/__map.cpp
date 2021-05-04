//
// Created by henri on 27/04/21.
//

#include "impl/__map.h"
#include "impl/__hash.h"

#include <stdexcept>

void state_machine_cpp::TransitionSet::add(const state_machine_cpp::State::Instance &t_instance) {
    m_transitions.emplace(hash<State::Instance>::get(t_instance), t_instance);
}

void state_machine_cpp::TransitionSet::remove(const state_machine_cpp::State::Instance &t_instance) {
    m_transitions.erase(hash<State::Instance>::get(t_instance));
}

bool state_machine_cpp::TransitionSet::has(const state_machine_cpp::State::Instance &t_instance) const {
    return m_transitions.find(hash<State::Instance>::get(t_instance)) != m_transitions.end();
}

state_machine_cpp::Transition::Any &
state_machine_cpp::TransitionSet::operator[](const state_machine_cpp::State::Instance &t_instance) {
    auto it = m_transitions.find(hash<State::Instance>::get(t_instance));
    if (it == m_transitions.end()) {
        throw std::runtime_error("Cannot access non-existing transition.");
    }
    return it->second;
}

const state_machine_cpp::Transition::Any &
state_machine_cpp::TransitionSet::operator[](const state_machine_cpp::State::Instance &t_instance) const {
    auto it = m_transitions.find(hash<State::Instance>::get(t_instance));
    if (it == m_transitions.end()) {
        throw std::runtime_error("Cannot access non-existing transition.");
    }
    return it->second;
}

state_machine_cpp::TransitionSet::const_iterator
state_machine_cpp::TransitionSet::find(const state_machine_cpp::State::Instance &t_instance) const {
    return const_iterator(
            m_transitions.find(hash<State::Instance>::get(t_instance))
        );
}

state_machine_cpp::TransitionSet::iterator
state_machine_cpp::TransitionSet::find(const state_machine_cpp::State::Instance &t_instance) {
    return iterator(
            m_transitions.find(hash<State::Instance>::get(t_instance))
            );
}


state_machine_cpp::TransitionSet::const_iterator state_machine_cpp::TransitionSet::begin() const {
    return const_iterator(m_transitions.begin());
}

state_machine_cpp::TransitionSet::const_iterator state_machine_cpp::TransitionSet::end() const {
    return const_iterator(m_transitions.end());
}

bool state_machine_cpp::TransitionSet::empty() const {
    return m_transitions.empty();
}

state_machine_cpp::TransitionSet::iterator state_machine_cpp::TransitionSet::begin() {
    return iterator(m_transitions.begin());
}

state_machine_cpp::TransitionSet::const_iterator state_machine_cpp::TransitionSet::cbegin() const {
    return const_iterator(m_transitions.cbegin());
}

state_machine_cpp::TransitionSet::iterator state_machine_cpp::TransitionSet::end() {
    return iterator(m_transitions.end());
}

state_machine_cpp::TransitionSet::const_iterator state_machine_cpp::TransitionSet::cend() const {
    return const_iterator(m_transitions.cend());
}
