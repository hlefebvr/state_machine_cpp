//
// Created by henri on 23/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_SANITY_CHECK_H
#define STATE_MACHINE_CPP_LIB_SANITY_CHECK_H

#include "explore.h"

namespace Algorithm {
    void sanity_check(const Algorithm::Instance& t_algorithm);
}

void Algorithm::sanity_check(const Algorithm::Instance& t_algorithm) {
    const auto& transitions = t_algorithm.transitions();

    for (const auto& transition : transitions) {

        const auto& state = transition.initial_state();
        const auto& successors = transition.next_states();

        if (successors.empty()) {
            std::cout << "WARNING(STATE_WITHOUT_ANY_SUCCESSOR), " << state << " has no successor" << std::endl;
        } else if (!transition.has_handler()) {
            std::cout << "WARNING(VIRTUAL_TRANSITION), " << state << " has a virtual transition" << std::endl;
        }

    }

}

#endif //STATE_MACHINE_CPP_LIB_SANITY_CHECK_H
