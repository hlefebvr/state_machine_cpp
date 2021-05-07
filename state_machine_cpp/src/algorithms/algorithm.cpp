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
    if (!has(t_instance)) {
        throw std::runtime_error("Cannot remove a non-existing state instance");
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
        throw std::runtime_error("Cannot create a transition from a non-existing state."
                                 "Initial state: " + t_initial_instance.name());
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


void state_machine_cpp::Algorithm::Instance::create_transition(const State::Instance &t_initial_instance,
                                            const State::Instance &t_next_instance,
                                            Transition::TrivialHandler *t_handler,
                                            bool t_is_override) {

    auto handler = t_handler ?
            [t_handler](Context& t_context){ (*t_handler)(t_context); return 0; } :
            std::function<int(Context&)>();

    create_any_transition(t_initial_instance,
                          Transition::Type::Direct,
                          { t_next_instance },
                          std::move(handler),
                          t_is_override);

}

void state_machine_cpp::Algorithm::Instance::create_transition_if(const State::Instance &t_initial_instance,
                                               const State::Instance &t_if_instance,
                                               const State::Instance &t_else_instance,
                                               Transition::ConditionalHandler *t_handler,
                                               bool t_is_override) {

    auto handler = t_handler ?
            [t_handler](Context& t_context){ return (*t_handler)(t_context); } :
            std::function<int(Context&)>();

    create_any_transition(t_initial_instance, Transition::Type::Conditional, { t_else_instance, t_if_instance }, std::move(handler), t_is_override);

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
    if (it == m_transitions.end()) {
        throw std::runtime_error("Cannot declare a non-existing transition as final.");
    }
    if (!it->has_handler()) {
        throw std::runtime_error("Cannot declare a virtual transition as final.");
    }
    it->set_as_final();
}
