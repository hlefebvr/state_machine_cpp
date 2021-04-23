//
// Created by henri on 22/04/21.
//

#include "AlgorithmInstance.h"

bool Algorithm::Instance::has(const State::Instance &t_instance) const {
    return m_transitions.find(t_instance) != m_transitions.end();
}

void Algorithm::Instance::create_state(const State::Instance& t_instance) {
    if (has(t_instance)) {
        throw std::runtime_error("Cannot create twice the same state instance.");
    }
    m_transitions.emplace(t_instance);
}

void Algorithm::Instance::remove_state(const State::Instance& t_instance) {
    if (!has(t_instance)) {
        throw std::runtime_error("Cannot remove a non-existing state instance");
    }
    m_transitions.erase(t_instance);
}

void Algorithm::Instance::create_any_transition(const State::Instance &t_initial_instance,
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

    }

    it->set_handler(std::move(t_next_states), std::move(t_handler));
}


void Algorithm::Instance::create_transition(const State::Instance &t_initial_instance,
                                            const State::Instance &t_next_instance,
                                            Transition::TrivialHandler *t_handler,
                                            bool t_should_already_exist) {

    auto handler = t_handler ?
            [t_handler](Context& t_context){ (*t_handler)(t_context); return 0; } :
            std::function<int(Context&)>();

    create_any_transition(t_initial_instance,{ t_next_instance }, std::move(handler), t_should_already_exist);

}

void Algorithm::Instance::create_transition_if(const State::Instance &t_initial_instance,
                                               const State::Instance &t_if_instance,
                                               const State::Instance &t_else_instance,
                                               Transition::ConditionalHandler *t_handler,
                                               bool t_should_already_exist) {

    auto handler = t_handler ?
            [t_handler](Context& t_context){ return (*t_handler)(t_context); } :
            std::function<int(Context&)>();

    create_any_transition(t_initial_instance,{ t_else_instance, t_if_instance }, std::move(handler), t_should_already_exist);

}

void Algorithm::Instance::remove_transition(const State::Instance &t_instance) {
    auto it = m_transitions.find(t_instance);
    if (it == m_transitions.end() || !it->has_handler()) {
        throw std::runtime_error("Cannot remove a non-existing transition instance");
    }
    it->reset_handler();
}

void Algorithm::Instance::run(Context &t_context, const State::Id& t_initial_state, const State::Id& t_final_state) const {

    State::Instance current_state = t_initial_state;
    do {
        current_state = apply_transition(current_state, t_context);
    } while (current_state != t_final_state);
    current_state = apply_transition(current_state, t_context);

}

const State::Instance &
Algorithm::Instance::apply_transition(const State::Instance &t_instance, Context &t_context) const {
    return m_transitions.find(t_instance)->operator()(t_context);
}

const Algorithm::Instance::Set<Transition::Any> &Algorithm::Instance::transitions() const {
    return m_transitions;
}
