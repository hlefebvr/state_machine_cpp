//
// Created by henri on 22/04/21.
//

#include "TransitionHandlerTrivial.h"

Transition::Handler::Trivial::Trivial(const State::Instance &t_next_instance,
                                      Transition::TrivialHandler &t_function)
    : m_function(&t_function), m_next_state(t_next_instance) {

}

const State::Instance &Transition::Handler::Trivial::operator()(Context &t_context) const {
    (*m_function)(t_context);
    return m_next_state;
}
