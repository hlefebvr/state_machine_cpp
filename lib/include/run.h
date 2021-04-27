//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_RUN_H
#define STATE_MACHINE_CPP_RUN_H

namespace state_machine_cpp {
    class Context;
    namespace State {
        class Id;
    }
    namespace Algorithm {
        class Instance;
        void run(const Algorithm::Instance &t_instance,
                 Context &t_context,
                 const State::Id &t_initial_state,
                 const State::Id &t_final_state);
    }
}

#endif //STATE_MACHINE_CPP_RUN_H
