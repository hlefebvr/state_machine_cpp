//
// Created by henri on 22/04/21.
//

#include "algorithm.h"

bool state_machine_cpp::Algorithm::Instance::has(const State::Instance &t_instance) const {
    return m_transitions.find(hash<State::Instance>::get(t_instance)) != m_transitions.end();
}

void state_machine_cpp::Algorithm::Instance::create_state(const State::Instance& t_instance) {
    if (has(t_instance)) {
        throw std::runtime_error("Cannot create twice the same state instance.");
    }
    m_transitions.emplace(hash<State::Instance>::get(t_instance), t_instance);
}

void state_machine_cpp::Algorithm::Instance::remove_state(const State::Instance& t_instance) {
    if (!has(t_instance)) {
        throw std::runtime_error("Cannot remove a non-existing state instance");
    }
    m_transitions.erase(hash<State::Instance>::get(t_instance));
}

void state_machine_cpp::Algorithm::Instance::create_any_transition(const State::Instance &t_initial_instance,
                                                std::vector<State::Instance> &&t_next_states,
                                                std::function<int(Context&)>&& t_handler,
                                                bool t_should_already_exist) {

    if (!has(t_initial_instance)) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + t_initial_instance.name());
    }

    for (const auto& instance : t_next_states) {
        if (!has(instance)) {
            throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                     + instance.name());
        }
    }

    auto it = m_transitions.find(hash<State::Instance>::get(t_initial_instance));

    if (!it->second.has_handler()) {

        if (t_should_already_exist) {
            throw std::runtime_error("Cannot override a non-existing transition. Use create. "
                                     "Initial state: " + t_initial_instance.name());
        }

    } else {

        if (!t_should_already_exist) {
            throw std::runtime_error("Cannot create twice the same transition. Use override. "
                                     "Initial state: " + t_initial_instance.name());
        }

        if (it->second.is_final()) {
            throw std::runtime_error("Cannot override a final transition. "
                                     "Initial state: " + t_initial_instance.name());
        }

    }

    it->second.set_handler(std::move(t_next_states), std::move(t_handler));
}


void state_machine_cpp::Algorithm::Instance::create_transition(const State::Instance &t_initial_instance,
                                            const State::Instance &t_next_instance,
                                            Transition::TrivialHandler *t_handler,
                                            bool t_should_already_exist) {

    auto handler = t_handler ?
            [t_handler](Context& t_context){ (*t_handler)(t_context); return 0; } :
            std::function<int(Context&)>();

    create_any_transition(t_initial_instance,{ t_next_instance }, std::move(handler), t_should_already_exist);

}

void state_machine_cpp::Algorithm::Instance::create_transition_if(const State::Instance &t_initial_instance,
                                               const State::Instance &t_if_instance,
                                               const State::Instance &t_else_instance,
                                               Transition::ConditionalHandler *t_handler,
                                               bool t_should_already_exist) {

    auto handler = t_handler ?
            [t_handler](Context& t_context){ return (*t_handler)(t_context); } :
            std::function<int(Context&)>();

    create_any_transition(t_initial_instance,{ t_else_instance, t_if_instance }, std::move(handler), t_should_already_exist);

}

void state_machine_cpp::Algorithm::Instance::remove_transition(const State::Instance &t_instance) {
    auto it = m_transitions.find(hash<State::Instance>::get(t_instance));
    if (it == m_transitions.end() || !it->second.has_handler()) {
        throw std::runtime_error("Cannot remove a non-existing transition instance.");
    }
    if (it->second.is_final()) {
        throw std::runtime_error("Cannot remove a transition declared final.");
    }
    it->second.reset_handler();
}

const state_machine_cpp::Algorithm::Instance::Set<state_machine_cpp::Transition::Any> &state_machine_cpp::Algorithm::Instance::transitions() const {
    return m_transitions;
}

void state_machine_cpp::Algorithm::Instance::set_as_final(const State::Instance &t_instance) {
    auto it = m_transitions.find(hash<State::Instance>::get(t_instance));
    if (it == m_transitions.end()) {
        throw std::runtime_error("Cannot declare a non-existing transition as final.");
    }
    if (!it->second.has_handler()) {
        throw std::runtime_error("Cannot declare a virtual transition as final.");
    }
    it->second.set_as_final();
}
