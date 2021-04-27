//
// Created by henri on 27/04/21.
//

#include "sanity_check.h"
#include "algorithm.h"

bool state_machine_cpp::Algorithm::sanity_check(const Algorithm::Instance& t_algorithm) {

    bool result = true;
    const auto& transitions = t_algorithm.transitions();

    if (transitions.empty()) {
        std::cout << "WARNING(EMPTY_ALGORITHM), the algorithm instance is empty" << std::endl;
        result = false;
    }

    for (const auto& [hash, transition] : transitions) {

        const auto& state = transition.initial_state();
        const auto& successors = transition.next_states();

        if (successors.empty()) {
            std::cout << "WARNING(STATE_WITHOUT_ANY_SUCCESSOR), " << state << " has no successor" << std::endl;
            result = false;
        } else if (!transition.has_handler()) {
            std::cout << "WARNING(VIRTUAL_TRANSITION), " << state << " has a virtual transition" << std::endl;
            result = false;
        }

    }

    return result;
}
