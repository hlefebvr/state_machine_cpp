//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITION_HANDLERS_H
#define STATE_MACHINE_CPP_TRANSITION_HANDLERS_H


namespace state_machine_cpp {
    class Context;

    namespace Transition {

        using TrivialHandler = void(Context &);
        using ConditionalHandler = bool(const Context &);

        void DO_NOTHING(Context &);
    }
}

#endif //STATE_MACHINE_CPP_TRANSITION_HANDLERS_H
