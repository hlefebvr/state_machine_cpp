//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITIONHANDLERANY_H
#define STATE_MACHINE_CPP_TRANSITIONHANDLERANY_H

class Context;

namespace State {
    class Instance;
}

namespace Transition {
    namespace Handler {
        class Any;
    }
}

class Transition::Handler::Any {
public:
    virtual const State::Instance& operator()(Context& t_context) const = 0;
};

#endif //STATE_MACHINE_CPP_TRANSITIONHANDLERANY_H
