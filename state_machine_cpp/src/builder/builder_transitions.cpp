//
// Created by henri on 27/04/21.
//

#include "builder/builder_transitions.h"

state_machine_cpp::Algorithm::Builder::Transitions::Transitions(const Layers* t_layer) : Indirection(t_layer) {

}

void state_machine_cpp::Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state,
                                                                Transition::TrivialHandler& t_handler) {
    create_or_override(false, t_initial_state, t_next_state, &t_handler);
}

void state_machine_cpp::Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state,
                                                                  Transition::TrivialHandler& t_handler) {
    create_or_override(true, t_initial_state, t_next_state, &t_handler);
}

void state_machine_cpp::Algorithm::Builder::Transitions::create_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                                   const State::Any &t_else, Transition::ConditionalHandler &t_handler) {
    create_or_override_if(false, t_initial_state, t_if_true, t_else, &t_handler);
}

void state_machine_cpp::Algorithm::Builder::Transitions::override_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                                     const State::Any &t_else, Transition::ConditionalHandler& t_handler) {
    create_or_override_if(true, t_initial_state, t_if_true, t_else, &t_handler);
}

void state_machine_cpp::Algorithm::Builder::Transitions::create_virtual(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(false, t_initial_state, t_next_state, nullptr);
}

void state_machine_cpp::Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(true, t_initial_state, t_next_state, &Transition::DO_NOTHING);
}

void state_machine_cpp::Algorithm::Builder::Transitions::create_if_virtual(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                                           const State::Any &t_else) {
    create_or_override_if(false, t_initial_state, t_if_true, t_else, nullptr);
}

void state_machine_cpp::Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(false, t_initial_state, t_next_state, &Transition::DO_NOTHING);
}
