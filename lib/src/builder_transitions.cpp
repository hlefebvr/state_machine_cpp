//
// Created by henri on 22/04/21.
//

#include "algorithm.h"

Algorithm::Impl::Build::Transitions::Transitions(Algorithm::Instance &t_destination, unsigned int t_level)
        : Algorithm::Builder::Transitions(t_level), m_destination(t_destination) {

}


void Algorithm::Impl::Build::Transitions::create_or_override(bool t_do_override,
                                                             const State::Any &t_initial_state,
                                                             const State::Any &t_next_state,
                                                             Transition::TrivialHandler *t_handler) {
    m_destination.create_transition(
            as_instance(t_initial_state),
            as_instance(t_next_state),
            t_handler,
            t_do_override);
}

void Algorithm::Impl::Build::Transitions::create_or_override_if(bool t_do_override,
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

void Algorithm::Impl::Build::Transitions::remove(const State::Any &t_state) {
    m_destination.remove_transition(as_instance(t_state));
}

void Algorithm::Impl::Build::Transitions::declare_as_final(const State::Any &t_state) {
    m_destination.set_as_final(as_instance(t_state));
}
