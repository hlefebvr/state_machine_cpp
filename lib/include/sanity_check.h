//
// Created by henri on 23/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_SANITY_CHECK_H
#define STATE_MACHINE_CPP_LIB_SANITY_CHECK_H

namespace state_machine_cpp {
    namespace Algorithm {
        bool sanity_check(const Algorithm::Instance &t_algorithm);
    }
}

bool state_machine_cpp::Algorithm::sanity_check(const Algorithm::Instance& t_algorithm) {

    bool result = true;
    const auto& transitions = t_algorithm.transitions();

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
        } else if (!transition.has_handler()) {
            std::cout << "WARNING(VIRTUAL_TRANSITION), " << state << " has a virtual transition" << std::endl;
            result = false;
        }

    }

    return result;
}

#endif //STATE_MACHINE_CPP_LIB_SANITY_CHECK_H
