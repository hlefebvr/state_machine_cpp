//
// Created by henri on 27/04/21.
//

#include "builder/builder_impl_transitions.h"
#include "algorithms/algorithm.h"

state_machine_cpp::Algorithm::Impl::Build::Transitions::Transitions(state_machine_cpp::Algorithm::Instance &t_destination,
                                                                    const state_machine_cpp::Algorithm::Builder::Layers* t_layer)
        : Algorithm::Builder::Transitions(t_layer), m_destination(t_destination) {

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
