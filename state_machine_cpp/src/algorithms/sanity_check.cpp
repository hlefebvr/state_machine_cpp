//
// Created by henri on 27/04/21.
//

#include "algorithms/sanity_check.h"
#include "algorithms/algorithm.h"

bool state_machine_cpp::Algorithm::sanity_check(const Algorithm::Instance& t_algorithm) {

    bool result = true;
    const auto& transitions = t_algorithm.transitions();

    if (!t_algorithm.is_initial_state_set()) {
        std::cout << "WARNING(UNSET_INITIAL_STATE), the algorithm has no initial state configure" << std::endl;
    }

    if (!t_algorithm.is_final_state_set()) {
        std::cout << "WARNING(UNSET_FINAL_STATE), the algorithm has no final state configure" << std::endl;
    }

    if (transitions.empty()) {
        std::cout << "WARNING(EMPTY_ALGORITHM), the algorithm instance is empty" << std::endl;
        result = false;
    }

    for (const auto& transition : transitions) {

        const auto& state = transition.initial_state();
        const auto& successors = transition.next_states();

        if (successors.empty()) {
            std::cout << "WARNING(STATE_WITHOUT_ANY_SUCCESSOR), " << state << " has no successor" << std::endl;
            result = false;
        } else if (transition.is_virtual()) {
            std::cout << "WARNING(VIRTUAL_TRANSITION), " << state << " has a virtual transition" << std::endl;
            result = false;
        }

    }

    return result;
}
