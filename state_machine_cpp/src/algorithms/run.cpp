//
// Created by henri on 27/04/21.
//

#include "algorithms/run.h"
#include "algorithms/algorithm.h"
#include "context/context.h"

void ::state_machine_cpp::Algorithm::Impl::run(::state_machine_cpp::Context& t_context,
                                         const ::state_machine_cpp::State::Id& t_initial_state,
                                         const ::state_machine_cpp::State::Id& t_final_state,
                                         const std::function<State::Instance(const State::Instance &t_state, Context &t_context)>& t_apply_transition) {

    State::Instance current_state = t_initial_state;
    t_context.set_state(current_state);
    do {
        current_state = t_apply_transition(current_state, t_context);
        t_context.set_state(current_state);
    } while (current_state != t_final_state);
    current_state = t_apply_transition(current_state, t_context);

}

void ::state_machine_cpp::Algorithm::run(const ::state_machine_cpp::Algorithm::Instance& t_algorithm,
                                       ::state_machine_cpp::Context& t_context,
                                       const ::state_machine_cpp::State::Id& t_initial_state,
                                       const ::state_machine_cpp::State::Id& t_final_state) {

    const auto& transitions = t_algorithm.transitions();

    const auto apply_transition = [&](const State::Instance &t_instance, Context &t_context) {
        return transitions[t_instance](t_context);
    };

    Impl::run(t_context, t_initial_state, t_final_state, apply_transition);

}

void ::state_machine_cpp::Algorithm::run_with_logs(const ::state_machine_cpp::Algorithm::Instance& t_algorithm,
                                         ::state_machine_cpp::Context& t_context,
                                         const ::state_machine_cpp::State::Id& t_initial_state,
                                         const ::state_machine_cpp::State::Id& t_final_state) {

    const auto& transitions = t_algorithm.transitions();

    const auto apply_transition = [&](const State::Instance &t_instance, Context &t_context) {
        std::cout << "-- state: " << t_instance << std::endl;
        return transitions[t_instance](t_context);
    };

    Impl::run(t_context, t_initial_state, t_final_state, apply_transition);

}
