//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITIONHANDLERTRIVIAL_H
#define STATE_MACHINE_CPP_TRANSITIONHANDLERTRIVIAL_H

#include "TransitionHandlerAny.h"
#include "TransitionHandlerType.h"
#include "../states/StateInstance.h"

namespace Transition {
    namespace Handler {
        class Trivial;
    }
}

class Transition::Handler::Trivial : public Transition::Handler::Any {
    Transition::TrivialHandler* m_function;
    State::Instance m_next_state;
public:
    Trivial(const State::Instance& t_next_instance, Transition::TrivialHandler& t_function);

    const State::Instance &operator()(Context &t_context) const override;
};


#endif //STATE_MACHINE_CPP_TRANSITIONHANDLERTRIVIAL_H
