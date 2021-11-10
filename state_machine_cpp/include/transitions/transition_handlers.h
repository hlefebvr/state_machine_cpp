//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITION_HANDLERS_H
#define STATE_MACHINE_CPP_TRANSITION_HANDLERS_H


namespace state_machine_cpp {
    class Context2;

    namespace Transition {

        using TrivialHandler = void(Context2 &);
        using ConditionalHandler = bool(const Context2 &);

        void DO_NOTHING(Context2 &);

        enum struct Type : char { Undefined, Direct, Conditional, Parallelized };
    }
}

#endif //STATE_MACHINE_CPP_TRANSITION_HANDLERS_H
