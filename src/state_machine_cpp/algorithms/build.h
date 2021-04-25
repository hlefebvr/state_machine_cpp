//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILD_H
#define STATE_MACHINE_CPP_BUILD_H

#include "Builder.h"
#include "Builder_States.h"
#include "Builder_Transitions.h"

template<class T>
void Algorithm::build(Algorithm::Instance& t_destination) {

    Impl::Build::States states(t_destination, 0);
    Impl::Build::Transitions transitions(t_destination, 0);

    Algorithm::Builder::inherit<T>(states, transitions);

}

#endif //STATE_MACHINE_CPP_BUILD_H
