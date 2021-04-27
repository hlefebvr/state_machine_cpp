//
// Created by henri on 22/04/21.
//

#include "algorithm.h"

bool state_machine_cpp::Algorithm::Instance::has(const State::Instance &t_instance) const {
    return m_transitions.find(t_instance) != m_transitions.end();
}

void state_machine_cpp::Algorithm::Instance::create_state(const State::Instance& t_instance) {
    if (has(t_instance)) {
        throw std::runtime_error("Cannot create twice the same state instance.");
    }
    m_transitions.emplace(t_instance);
}

void state_machine_cpp::Algorithm::Instance::remove_state(const State::Instance& t_instance) {
    if (!has(t_instance)) {
        throw std::runtime_error("Cannot remove a non-existing state instance");
    }
    m_transitions.erase(t_instance);
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

    auto it = m_transitions.find(t_initial_instance);

    if (!it->has_handler()) {

        if (t_should_already_exist) {
            throw std::runtime_error("Cannot override a non-existing transition. Use create. "
                                     "Initial state: " + t_initial_instance.name());
        }

    } else {

        if (!t_should_already_exist) {
            throw std::runtime_error("Cannot create twice the same transition. Use override. "
                                     "Initial state: " + t_initial_instance.name());
        }

        if (it->is_final()) {
            throw std::runtime_error("Cannot override a final transition. "
                                     "Initial state: " + t_initial_instance.name());
        }

    }

    it->set_handler(std::move(t_next_states), std::move(t_handler));
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
    auto it = m_transitions.find(t_instance);
    if (it == m_transitions.end() || !it->has_handler()) {
        throw std::runtime_error("Cannot remove a non-existing transition instance.");
    }
    if (it->is_final()) {
        throw std::runtime_error("Cannot remove a transition declared final.");
    }
    it->reset_handler();
}

const state_machine_cpp::Algorithm::Instance::Set<state_machine_cpp::Transition::Any> &state_machine_cpp::Algorithm::Instance::transitions() const {
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

unsigned int state_machine_cpp::Algorithm::Impl::Build::Layers::current() const {
    return m_layers.empty() ? 0 : m_layers.top();
}

unsigned int state_machine_cpp::Algorithm::Impl::Build::Layers::create() {
    ++m_max_layer;
    m_layers.emplace(m_max_layer);
    return current();
}

unsigned int state_machine_cpp::Algorithm::Impl::Build::Layers::use(unsigned int t_layer) {
    if (t_layer > m_max_layer) {
        throw std::runtime_error("The level you are trying to use has not been created. Use create first.");
    }
    m_layers.emplace(t_layer);
    return current();
}

void state_machine_cpp::Algorithm::Impl::Build::Layers::close() {
    if (m_layers.empty()) {
        throw std::runtime_error("Cannot close root layer");
    }
    m_layers.pop();
}


state_machine_cpp::Algorithm::Impl::Build::States::States(state_machine_cpp::Algorithm::Instance &t_destination, const Layers* t_layer)
        : state_machine_cpp::Algorithm::Builder::States(t_layer), m_destination(t_destination) {

}

void state_machine_cpp::Algorithm::Impl::Build::States::create(const State::Any &t_state) {
    m_destination.create_state(as_instance(t_state));
}

void state_machine_cpp::Algorithm::Impl::Build::States::remove(const State::Any &t_state) {
    m_destination.remove_state(as_instance(t_state));
}


state_machine_cpp::Algorithm::Impl::Build::Transitions::Transitions(state_machine_cpp::Algorithm::Instance &t_destination, const Layers* t_layer)
        : state_machine_cpp::Algorithm::Builder::Transitions(t_layer), m_destination(t_destination) {

}


void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_or_override(bool t_do_override,
                                                             const State::Any &t_initial_state,
                                                             const State::Any &t_next_state,
                                                             Transition::TrivialHandler *t_handler) {
    m_destination.create_transition(
            as_instance(t_initial_state),
            as_instance(t_next_state),
            t_handler,
            t_do_override);
}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_or_override_if(bool t_do_override,
                                                                const State::Any &t_initial_state,
                                                                const State::Any &t_if_true,
                                                                const State::Any &t_else,
                                                                Transition::ConditionalHandler *t_handler) {

    m_destination.create_transition_if(
            as_instance(t_initial_state),
            as_instance(t_if_true),
            as_instance(t_else),
            t_handler,
            t_do_override);

}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::remove(const State::Any &t_state) {
    m_destination.remove_transition(as_instance(t_state));
}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::declare_as_final(const State::Any &t_state) {
    m_destination.set_as_final(as_instance(t_state));
}
