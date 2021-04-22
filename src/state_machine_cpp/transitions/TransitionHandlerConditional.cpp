//
// Created by henri on 22/04/21.
//

#include "TransitionHandlerConditional.h"

Transition::Handler::Conditional::Conditional(const State::Instance &t_if_instance,
                                              const State::Instance &t_else_instance,
                                              Transition::ConditionalHandler &t_function)
    : m_function(&t_function), m_if_state(t_if_instance), m_else_state(t_else_instance) {

}

const State::Instance &Transition::Handler::Conditional::operator()(Context &t_context) const {
    return (*m_function)(t_context) ? m_if_state : m_else_state;
}
