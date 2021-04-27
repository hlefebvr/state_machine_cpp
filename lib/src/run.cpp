//
// Created by henri on 27/04/21.
//

#include "run.h"
#include "algorithm.h"
#include "context.h"

void ::state_machine_cpp::Algorithm::run(const ::state_machine_cpp::Algorithm::Instance& t_algorithm,
                                       ::state_machine_cpp::Context& t_context,
                                       const ::state_machine_cpp::State::Id& t_initial_state,
                                       const ::state_machine_cpp::State::Id& t_final_state) {

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
