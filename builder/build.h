//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILD_H
#define STATE_MACHINE_CPP_BUILD_H

namespace Algorithm {
    template<class T> void build(Algorithm::Instance& t_destination);
}

template<class T>
void Algorithm::build(Algorithm::Instance& t_destination) {

    Builder::States states(t_destination, 0);
    Builder::Transitions transitions(t_destination, 0);

    T builder;
    builder.build(states, transitions);
}

#endif //STATE_MACHINE_CPP_BUILD_H
