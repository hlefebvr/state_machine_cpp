//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_H
#define STATE_MACHINE_CPP_BUILDER_H

#include <iostream>

namespace state_machine_cpp {
    namespace Algorithm {
        class Builder;
        class Instance;
        template<class T> void build(Algorithm::Instance& t_destination);
    }
}

class state_machine_cpp::Algorithm::Builder {
public:
    class States;
    class Transitions;
    class Layers;

    template<class T> friend void ::state_machine_cpp::Algorithm::build(Algorithm::Instance& t_destination);

    virtual void build(States& states, Transitions& transitions, Layers& layers) = 0;
protected:
    template<class T> static void inherit(States& states, Transitions& transitions, Layers& layers);
private:
    class Indirection;
};

template<class T>
void state_machine_cpp::Algorithm::Builder::inherit(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions, Layers& layers) {
    T builder;
    builder.build(states, transitions, layers);
}

#endif //STATE_MACHINE_CPP_BUILDER_H
