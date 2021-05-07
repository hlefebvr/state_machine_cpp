//
// Created by henri on 27/04/21.
//

#include "algorithms/run.h"
#include "algorithms/algorithm.h"
#include "context/context.h"

namespace state_machine_cpp::Algorithm::Impl {
    void throw_if_is_not_configured(const ::state_machine_cpp::Algorithm::Instance& t_algorithm) {
        if (!t_algorithm.is_initial_state_set()) {
            throw std::runtime_error("Trying to run an algorithm without initial state begin configure.\n\n"
                                     "-> If you are a user of the algorithm, use set_initial_state to configure it.\n\n"
                                     "-> If you are the creator of the algorithm builder, you should add a public static "
                                     "const State::Id attribute (or const State::Id& attribute) called INITIAL_STATE "
                                     "to allow for automatic detection of initial state.");
        }

        if (!t_algorithm.is_final_state_set()) {
            throw std::runtime_error("Trying to run an algorithm without final state begin configured.\n\n"
                                     "-> If you are a user of the algorithm, use set_final_state to configure it.\n\n"
                                     "-> If you are the creator of the algorithm builder, you should add a public static "
                                     "const State::Id attribute (or const State::Id& attribute) called FINAL_STATE "
                                     "to allow for automatic detection of final state.");
        }
    }
}

void ::state_machine_cpp::Algorithm::run(const ::state_machine_cpp::Algorithm::Instance& t_algorithm,
                                       ::state_machine_cpp::Context& t_context) {

    Impl::throw_if_is_not_configured(t_algorithm);

    const auto& transitions = t_algorithm.transitions();
    const State::Instance final_state = t_algorithm.final_state();

    const auto apply_transition = [&](const State::Instance &t_instance, Context &t_context) {
        return transitions[t_instance](t_context);
    };

    State::Instance current_state = t_algorithm.initial_state();
    t_context.set_state(current_state);
    do {
        current_state = apply_transition(current_state, t_context);
        t_context.set_state(current_state);
    } while (current_state != final_state);
    current_state = apply_transition(current_state, t_context);

}
