//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITIONHANDLER_H
#define STATE_MACHINE_CPP_TRANSITIONHANDLER_H

class Context;

namespace Transition {
    using TrivialHandler = void(Context&);
    using ConditionalHandler = bool(Context&);
}

#endif //STATE_MACHINE_CPP_TRANSITIONHANDLER_H
