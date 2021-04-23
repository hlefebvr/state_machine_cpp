//
// Created by henri on 21/04/21.
//

#include "Builder.h"

Algorithm::Builder::Indirection::Indirection(unsigned int t_level) : m_level(t_level) {

}

unsigned int Algorithm::Builder::Indirection::level() const {
    return m_level;
}

State::Instance Algorithm::Builder::Indirection::as_instance(const State::Any &t_any) const {
    return t_any.as_instance(m_level);
}

Algorithm::Builder::States::States(unsigned int t_level) : Indirection(t_level) {

}

Algorithm::Builder::Transitions::Transitions(unsigned int t_level) : Indirection(t_level) {

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

void Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(false, t_initial_state, t_next_state, nullptr);
}

void Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state) {
    create_or_override(true, t_initial_state, t_next_state, nullptr);
}

void Algorithm::Builder::Transitions::create_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                const State::Any &t_else) {
    create_or_override_if(false, t_initial_state, t_if_true, t_else, nullptr);
}

void Algorithm::Builder::Transitions::override_if(const State::Any &t_initial_state, const State::Any &t_if_true,
                                                  const State::Any &t_else) {
    create_or_override_if(true, t_initial_state, t_if_true, t_else, nullptr);
}
