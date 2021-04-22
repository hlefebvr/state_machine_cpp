//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_ALGORITHMINSTANCE_H
#define STATE_MACHINE_CPP_ALGORITHMINSTANCE_H

#include "Builder.h"

namespace Algorithm {
    class Instance;
}

class Algorithm::Instance {
    friend class Algorithm::Builder::States;
    void create_state(const State::Instance& t_instance);
    void remove_state(const State::Instance& t_instance);

    friend class Algorithm::Builder::Transitions;
    void create_transition(const State::Instance& t_initial_instance,
                           const State::Instance& t_next_instance,
                           Transition::TrivialHandler& t_handler,
                           bool t_should_already_exist);
    void remove_transition(const State::Instance& t_instance);
public:

};


#endif //STATE_MACHINE_CPP_ALGORITHMINSTANCE_H
