//
// Created by henri on 21/04/21.
//

#include "Builder.h"
#include "AlgorithmInstance.h"

State::Instance Algorithm::Builder::as_instance(const State::Any &t_state, unsigned int t_level_if_not_set) {
    return t_state.is_instantiated() ? t_state.as_provided() : t_state.instantiate(t_level_if_not_set);
}

Algorithm::Builder::Indirection::Indirection(Algorithm::Instance &t_destination, unsigned int t_level)
    : m_destination(t_destination), m_level(t_level) {

}

Algorithm::Instance &Algorithm::Builder::Indirection::destination() {
    return m_destination;
}

unsigned int Algorithm::Builder::Indirection::level() const {
    return m_level;
}

void Algorithm::Builder::States::create(const State::Any& t_state) {
    auto instance = as_instance(t_state, level());
    destination().create_state(instance);
}

void Algorithm::Builder::States::remove(const State::Any& t_state) {
    auto instance = as_instance(t_state, level());
    destination().remove_state(instance);
}

Algorithm::Builder::States::States(Algorithm::Instance &t_destination, unsigned int t_level)
    : Indirection(t_destination, t_level) {

}

Algorithm::Builder::Transitions::Transitions(Algorithm::Instance &t_destination, unsigned int t_level)
    : Indirection(t_destination, t_level) {

}

void Algorithm::Builder::Transitions::create_or_override(bool t_do_override, const State::Any &t_initial_state, const State::Any &t_next_state,
                                             Transition::TrivialHandler& t_handler) {
    auto initial_instance = Builder::as_instance(t_initial_state, level());
    auto next_instance = Builder::as_instance(t_next_state, level());
    destination().create_transition(initial_instance, next_instance, t_handler, t_do_override);
}

void Algorithm::Builder::Transitions::create(const State::Any &t_initial_state, const State::Any &t_next_state,
                                             Transition::TrivialHandler& t_handler) {
    create_or_override(false, t_initial_state, t_next_state, t_handler);
}

void Algorithm::Builder::Transitions::override(const State::Any &t_initial_state, const State::Any &t_next_state,
                                             Transition::TrivialHandler& t_handler) {
    create_or_override(true, t_initial_state, t_next_state, t_handler);
}

void Algorithm::Builder::Transitions::remove(const State::Any &t_state) {
    auto instance = Builder::as_instance(t_state, level());
    destination().remove_transition(instance);
}
