//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_RUN_H
#define STATE_MACHINE_CPP_RUN_H

#include <functional>
#include "states/state_instance.h"

namespace state_machine_cpp {
    class Context;
    namespace State {
        class Id;
    }
    namespace Algorithm {
        namespace Impl {
            void run(Context &t_context,
                     const State::Id &t_initial_state,
                     const State::Id &t_final_state,
                     const std::function<State::Instance(const State::Instance &t_state, Context &t_context)>& t_apply_transition);
        }
        class Instance;
        void run(const Algorithm::Instance &t_instance,
                 Context &t_context,
                 const State::Id &t_initial_state,
                 const State::Id &t_final_state);

        void run_with_logs(const Algorithm::Instance &t_instance,
                 Context &t_context,
                 const State::Id &t_initial_state,
                 const State::Id &t_final_state);
    }
}

#endif //STATE_MACHINE_CPP_RUN_H
