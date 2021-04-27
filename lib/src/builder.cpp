//
// Created by henri on 21/04/21.
//

#include "builder.h"

Algorithm::Builder::Indirection::Indirection(const Layers* t_layers) : m_layers(t_layers) {

}

State::Instance Algorithm::Builder::Indirection::as_instance(const State::Any &t_any) const {
    return t_any.as_instance(m_layers->current());
}

Algorithm::Builder::States::States(const Layers* t_layer) : Indirection(t_layer) {

}

Algorithm::Builder::Transitions::Transitions(const Layers* t_layer) : Indirection(t_layer) {

}

void Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state,
                                             Transition::TrivialHandler& t_handler) {
    create_or_override(false, t_initial_state, t_next_state, &t_handler);
}

void Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state,
                                             Transition::TrivialHandler& t_handler) {
    create_or_override(true, t_initial_state, t_next_state, &t_handler);
}

void Algorithm::Builder::Transitions::create_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                const State::Any &t_else, Transition::ConditionalHandler &t_handler) {
    create_or_override_if(false, t_initial_state, t_if_true, t_else, &t_handler);
}

void Algorithm::Builder::Transitions::override_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                  const State::Any &t_else, Transition::ConditionalHandler& t_handler) {
    create_or_override_if(true, t_initial_state, t_if_true, t_else, &t_handler);
}

void Algorithm::Builder::Transitions::create_virtual(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(false, t_initial_state, t_next_state, nullptr);
}

void Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(true, t_initial_state, t_next_state, &Transition::DO_NOTHING);
}

void Algorithm::Builder::Transitions::create_if_virtual(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                        const State::Any &t_else) {
    create_or_override_if(false, t_initial_state, t_if_true, t_else, nullptr);
}

void Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(false, t_initial_state, t_next_state, &Transition::DO_NOTHING);
}
