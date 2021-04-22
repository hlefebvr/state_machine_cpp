//
// Created by henri on 22/04/21.
//

#include <cassert>
#include "TransitionAny.h"

Transition::Any::Any(const State::Instance &t_initial_state) : m_initial_state(t_initial_state) {

}

void Transition::Any::set_handler(Transition::Handler::Any *t_handler) {
    m_handler.reset(t_handler);
}

const State::Instance &Transition::Any::operator()(Context &t_context) const {
    assert(!!m_handler);
    return (*m_handler)(t_context);
}

bool Transition::Any::has_handler() const {
    return (bool) m_handler;
}
