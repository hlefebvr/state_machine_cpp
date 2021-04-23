//
// Created by henri on 22/04/21.
//

#include "AlgorithmTransitionsPlotter.h"

Algorithm::Impl::Explorer::Transitions::Transitions(
        robin_hood::unordered_map<std::string, std::list<std::string>>& t_transitions,
        unsigned int t_level) : Algorithm::Builder::Transitions(t_level), m_transitions(t_transitions) {

}

void Algorithm::Impl::Explorer::Transitions::remove(const State::Any &t_state) {

    auto instance = as_instance(t_state);
    auto it = m_transitions.find(instance.name());
    if (it == m_transitions.end() || it->second.empty()) {
        throw std::runtime_error("Cannot remove a non-existing transition instance");
    }
    it->second.clear();

}

void Algorithm::Impl::Explorer::Transitions::create_any_transition(const State::Instance &t_initial_instance,
                                                               std::list<std::string> &&t_list,
                                                               bool t_should_already_exist) {

    auto it = m_transitions.find(t_initial_instance.name());

    if (it->second.empty()) {

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

    it->second = std::move(t_list);

}

void Algorithm::Impl::Explorer::Transitions::create_or_override(bool t_do_override,
                                                            const State::Any &t_initial_state,
                                                            const State::Any &t_next_state,
                                                            Transition::TrivialHandler &t_handler) {

    if (!has(as_instance(t_initial_state))) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + as_instance(t_initial_state).name());
    }

    if (!has(as_instance(t_next_state))) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + as_instance(t_next_state).name());
    }

    create_any_transition(
            as_instance(t_initial_state),
            { as_instance(t_next_state).name() },
            t_do_override
        );

}

void Algorithm::Impl::Explorer::Transitions::create_or_override_if(bool t_do_override,
                                                               const State::Any &t_initial_state,
                                                               const State::Any &t_if_true,
                                                               const State::Any &t_else,
                                                               Transition::ConditionalHandler &t_handler) {

    if (!has(as_instance(t_initial_state))) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + as_instance(t_initial_state).name());
    }

    if (!has(as_instance(t_if_true))) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + as_instance(t_if_true).name());
    }

    if (!has(as_instance(t_else))) {
        throw std::runtime_error("Cannot create a transition on a non-existing state. State: "
                                 + as_instance(t_else).name());
    }

    create_any_transition(
            as_instance(t_initial_state),
            { as_instance(t_if_true).name(), as_instance(t_else).name() },
            t_do_override
    );

}

bool Algorithm::Impl::Explorer::Transitions::has(const State::Instance &t_instance) const {
    return m_transitions.find(t_instance.name()) != m_transitions.end();
}
