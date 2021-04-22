//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITIONHANDLERCONDITIONAL_H
#define STATE_MACHINE_CPP_TRANSITIONHANDLERCONDITIONAL_H

#include "TransitionHandlerAny.h"
#include "TransitionHandlerType.h"
#include "../states/StateInstance.h"

namespace Transition {
    namespace Handler {
        class Conditional;
    }
}

class Transition::Handler::Conditional : public Transition::Handler::Any {
    Transition::ConditionalHandler* m_function;
    State::Instance m_if_state;
    State::Instance m_else_state;
public:
    Conditional(const State::Instance& t_if_instance, const State::Instance& t_else_instance, Transition::ConditionalHandler& t_function);
    const State::Instance &operator()(Context &t_context) const override;
};

#endif //STATE_MACHINE_CPP_TRANSITIONHANDLERCONDITIONAL_H
