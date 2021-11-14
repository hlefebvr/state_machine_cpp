//
// Created by henri on 27/04/21.
//

#include "builder/builder_transitions.h"

state_machine_cpp::Algorithm::Builder::Transitions::Transitions(Algorithm::Instance& t_destination, const Layers* t_layer, Algorithm::Mode t_build_mode)
    : Indirection(t_destination, t_layer, t_build_mode) {

}

void state_machine_cpp::Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state,
                                                                Transition::TrivialHandler& t_handler, std::string t_description) {
    create_or_override(false, t_initial_state, t_next_state, &t_handler, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state,
                                                                  Transition::TrivialHandler& t_handler, std::string t_description) {
    create_or_override(true, t_initial_state, t_next_state, &t_handler, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::create_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                                   const State::Any &t_else, Transition::ConditionalHandler &t_handler, std::string t_description) {
    create_or_override_if(false, t_initial_state, t_if_true, t_else, &t_handler, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::override_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                                     const State::Any &t_else, Transition::ConditionalHandler& t_handler, std::string t_description) {
    create_or_override_if(true, t_initial_state, t_if_true, t_else, &t_handler, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::create_virtual(const State::Any &t_initial_state, const State::Any &t_next_state, std::string t_description) {
    create_or_override(false, t_initial_state, t_next_state, nullptr, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state, std::string t_description) {
    create_or_override(true, t_initial_state, t_next_state, &Transition::DO_NOTHING, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::create_if_virtual(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                                           const State::Any &t_else, std::string t_description) {
    create_or_override_if(false, t_initial_state, t_if_true, t_else, nullptr, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state, std::string t_description) {
    create_or_override(false, t_initial_state, t_next_state, &Transition::DO_NOTHING, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::create_parallelized(const state_machine_cpp::State::Any &t_initial_state, std::initializer_list<State::Any> t_next_states, const state_machine_cpp::State::Any &t_final_state, std::string t_description) {
    create_or_override_parallelized(false, t_initial_state, t_next_states, t_final_state, std::move(t_description));
}

void state_machine_cpp::Algorithm::Builder::Transitions::override_parallelized(const state_machine_cpp::State::Any &t_initial_state, std::initializer_list<State::Any> t_next_states, const state_machine_cpp::State::Any &t_final_state, std::string t_description) {
    create_or_override_parallelized(true, t_initial_state, t_next_states, t_final_state, std::move(t_description));
}
