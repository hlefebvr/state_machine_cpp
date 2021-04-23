//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITIONHANDLERTYPE_H
#define STATE_MACHINE_CPP_TRANSITIONHANDLERTYPE_H

class Context;

namespace Transition {

    using TrivialHandler = void(Context&);
    using ConditionalHandler = bool(const Context&);

    void DO_NOTHING(Context&);

}

#endif //STATE_MACHINE_CPP_TRANSITIONHANDLERTYPE_H
