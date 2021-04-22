//
// Created by henri on 22/04/21.
//

#include "AlgorithmInstance.h"

void Algorithm::Instance::create_state(const State::Instance& t_instance) {
    std::cout << "CREATE STATE " << t_instance << std::endl;
}

void Algorithm::Instance::remove_state(const State::Instance& t_instance) {
    std::cout << "DELETE STATE " << t_instance << std::endl;
}

void Algorithm::Instance::create_transition(const State::Instance &t_initial_instance,
                                            const State::Instance &t_next_instance,
                                            Transition::TrivialHandler &t_handler,
                                            bool t_should_already_exist) {

    if (t_should_already_exist) {
        std::cout << "OVERRIDE ";
    } else {
        std::cout << "CREATE ";
    }
    std::cout << "TRANSITION FROM " << t_initial_instance << " TO " << t_next_instance << std::endl;

}

void Algorithm::Instance::remove_transition(const State::Instance &t_instance) {
    std::cout << "REMOVE TRANSITION " << t_instance << std::endl;
}
