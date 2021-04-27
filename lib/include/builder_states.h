//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_STATES_H
#define STATE_MACHINE_CPP_BUILDER_STATES_H

#include "builder_indirection.h"

class state_machine_cpp::Algorithm::Builder::States : public Indirection {
public:
    explicit States(const Layers* t_layer);

    virtual void create(const State::Any& t_state) = 0;
    virtual void remove(const State::Any& t_state) = 0;
};

#endif //STATE_MACHINE_CPP_BUILDER_STATES_H
