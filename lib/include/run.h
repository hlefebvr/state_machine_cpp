//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_RUN_H
#define STATE_MACHINE_CPP_RUN_H

#include "context.h"

namespace Algorithm {
    void run(const Algorithm::Instance& t_instance,
             Context& t_context,
             const State::Id& t_initial_state,
             const State::Id& t_final_state);
}

void Algorithm::run(const Algorithm::Instance& t_algorithm,
         Context& t_context,
         const State::Id& t_initial_state,
         const State::Id& t_final_state) {

    const auto& transitions = t_algorithm.transitions();

    const auto apply_transition = [&](const State::Instance &t_instance, Context &t_context) {
        auto it = transitions.find(t_instance);
        if (it == transitions.end()) {
            throw std::runtime_error("Algorithm execution failed: called an undefined transition.");
        }
        return it->operator()(t_context);
    };

    State::Instance current_state = t_initial_state;
    t_context.set_state(current_state);
    do {
        current_state = apply_transition(current_state, t_context);
        t_context.set_state(current_state);
    } while (current_state != t_final_state);
    current_state = apply_transition(current_state, t_context);


}

#endif //STATE_MACHINE_CPP_RUN_H
