//
// Created by henri on 22/04/21.
//

#include "AlgorithmInstance.h"
#include "../transitions/TransitionHandlerTrivial.h"
#include "../transitions/TransitionHandlerConditional.h"

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
                                                const std::function<Transition::Handler::Any *()> &t_handler_creator,
                                                bool t_should_already_exist) {
    auto it = m_transitions.find(t_initial_instance);

    if (!it->has_handler()) {

        if (t_should_already_exist) {
            throw std::runtime_error("Cannot override a non-existing transition. Use create. "
                                     "Initial state: " + t_initial_instance.name());
        }
        m_transitions.emplace(t_initial_instance).first->set_handler(t_handler_creator());

    } else {

        if (!t_should_already_exist) {
            throw std::runtime_error("Cannot create twice the same transition. Use override. "
                                     "Initial state: " + t_initial_instance.name());
        }
        m_transitions.find(t_initial_instance)->set_handler(t_handler_creator());

    }
}


void Algorithm::Instance::create_transition(const State::Instance &t_initial_instance,
                                            const State::Instance &t_next_instance,
                                            Transition::TrivialHandler &t_handler,
                                            bool t_should_already_exist) {

    if (!has(t_initial_instance)) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + t_initial_instance.name());
    }

    if (!has(t_next_instance)) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + t_next_instance.name());
    }

    create_any_transition(
            t_initial_instance,
            [&](){ return new Transition::Handler::Trivial(t_next_instance, t_handler); },
            t_should_already_exist
            );

}

void Algorithm::Instance::create_transition_if(const State::Instance &t_initial_instance,
                                               const State::Instance &t_if_instance,
                                               const State::Instance &t_else_instance,
                                               Transition::ConditionalHandler &t_handler,
                                               bool t_should_already_exist) {

    if (!has(t_initial_instance)) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + t_initial_instance.name());
    }

    if (!has(t_if_instance)) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + t_if_instance.name());
    }

    if (!has(t_else_instance)) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + t_else_instance.name());
    }

    create_any_transition(
            t_initial_instance,
            [&](){ return new Transition::Handler::Conditional(t_if_instance, t_else_instance, t_handler); },
            t_should_already_exist
    );

}

void Algorithm::Instance::remove_transition(const State::Instance &t_instance) {
    if (!has(t_instance)) {
        throw std::runtime_error("Cannot remove a non-existing transition instance");
    }
    m_transitions.find(t_instance)->set_handler(nullptr);
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
