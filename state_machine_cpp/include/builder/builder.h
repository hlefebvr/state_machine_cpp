//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_H
#define STATE_MACHINE_CPP_BUILDER_H

#include <iostream>
#include "states/state_instance.h"
#include "builder/builder_types.h"

namespace state_machine_cpp::Algorithm {
    class Builder;
    class Instance;
    template<class T> void build(Algorithm::Instance& t_destination, Algorithm::Mode t_build_mode = Algorithm::Mode::Release);
}

class state_machine_cpp::Algorithm::Builder {
public:
    class States;
    class Transitions;
    class Layers;

    template<class T> friend void ::state_machine_cpp::Algorithm::build(
        Algorithm::Instance& t_destination,
        Algorithm::Mode t_build_mode
    );

    virtual void build(States& states, Transitions& transitions, Layers& layers) = 0;
protected:
    template<class T> static void import(States& states, Transitions& transitions, Layers& layers);
private:
    class Indirection;
};

template<class T>
void state_machine_cpp::Algorithm::Builder::import(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions, Layers& layers) {
    T builder;
    builder.build(states, transitions, layers);
}

#endif //STATE_MACHINE_CPP_BUILDER_H
