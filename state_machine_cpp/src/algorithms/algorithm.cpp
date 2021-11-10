//
// Created by henri on 22/04/21.
//

#include "algorithms/algorithm.h"

bool state_machine_cpp::Algorithm::Instance::has(const State::Instance &t_instance) const {
    return m_transitions.has(t_instance);
}

void state_machine_cpp::Algorithm::Instance::create_state(const State::Instance& t_instance) {
    if (has(t_instance)) {
        throw std::runtime_error("Cannot create twice the same state instance.");
    }
    m_transitions.add(t_instance);
}

void state_machine_cpp::Algorithm::Instance::remove_state(const State::Instance& t_instance) {

    auto it = m_transitions.find(t_instance);

    if (it == m_transitions.end()) {
        throw std::runtime_error("Cannot remove a non-existing state instance");
    }

    if (it->has_handler()) {
        throw std::runtime_error("Cannot remove state " + t_instance.name() + " because other transitions depend on it.");
    }

    for (const auto& transition : m_transitions) {
        for (const auto& next_state : transition.next_states()) {
            if (next_state == t_instance) {
                throw std::runtime_error("Cannot remove state " + t_instance.name() + " because other transitions depend on it. "
                                              "Transition: " + transition.initial_state().name() + " -- " + next_state.name());
            }
        }
    }

    m_transitions.remove(t_instance);
}

void state_machine_cpp::Algorithm::Instance::create_any_transition(
                                                const State::Instance &t_initial_instance,
                                                Transition::Type t_transition_type,
                                                std::vector<State::Instance> &&t_next_states,
                                                std::function<int(Context&)>&& t_handler,
                                                bool t_is_override) {

    auto it = m_transitions.find(t_initial_instance);

    if (it == m_transitions.end()) {
        throw std::runtime_error("Cannot create or override a transition from a non-existing state. "
                                 "Initial state: " + t_initial_instance.name());
    }

    for (const auto& next_state : t_next_states) {
        if (!m_transitions.has(next_state)) {
            throw std::runtime_error("Cannot create or override a transition to a non-existing state. "
                                     "Next state: " + next_state.name());
        }
    }

    if (!it->has_handler()) {

        if (t_is_override && !it->is_virtual()) {
            throw std::runtime_error("Cannot override a non-existing transition. Use create. "
                                     "Initial state: " + t_initial_instance.name());
        }

        if (!t_is_override && it->is_virtual()) {
            throw std::runtime_error("Cannot create twice the same transition. Use override. "
                                     "Initial state: " + t_initial_instance.name());
        }

    } else {

        if (!t_is_override) {
            throw std::runtime_error("Cannot create twice the same transition. Use override. "
                                     "Initial state: " + t_initial_instance.name());
        }

        if (it->is_final()) {
            throw std::runtime_error("Cannot override a final transition. "
                                     "Initial state: " + t_initial_instance.name());
        }

    }

    it->set_handler(t_transition_type, std::move(t_next_states), std::move(t_handler));
}

void state_machine_cpp::Algorithm::Instance::remove_transition(const State::Instance &t_instance) {
    auto it = m_transitions.find(t_instance);
    if (it == m_transitions.end() || !it->has_handler()) {
        throw std::runtime_error("Cannot remove a non-existing transition instance.");
    }
    if (it->is_final()) {
        throw std::runtime_error("Cannot remove a transition declared final.");
    }
    it->reset_handler();
}

const state_machine_cpp::TransitionSet &state_machine_cpp::Algorithm::Instance::transitions() const {
    return m_transitions;
}

void state_machine_cpp::Algorithm::Instance::set_as_final(const State::Instance &t_instance) {
    auto it = m_transitions.find(t_instance);
    if (it == m_transitions.end() || !it->has_handler()) {
        throw std::runtime_error("Cannot declare a non-existing transition as final.");
    }
    if (it->is_virtual()) {
        throw std::runtime_error("Cannot declare a virtual transition as final.");
    }
    it->set_as_final();
}
