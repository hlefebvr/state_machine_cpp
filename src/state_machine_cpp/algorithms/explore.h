//
// Created by henri on 23/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_EXPLORE_H
#define STATE_MACHINE_CPP_LIB_EXPLORE_H

#include <list>
#include "Explorer_Transitions.h"
#include "Explorer_States.h"

namespace Algorithm {
    template<class T> robin_hood::unordered_map<std::string, std::list<std::string>> explore();
}

template<class T>
robin_hood::unordered_map<std::string, std::list<std::string>>
Algorithm::explore() {

    robin_hood::unordered_map<std::string, std::list<std::string>> result;

    Impl::Explorer::States states(result, 0);
    Impl::Explorer::Transitions transitions(result, 0);

    T builder;
    builder.build(states, transitions);

    return result;
}

#endif //STATE_MACHINE_CPP_LIB_EXPLORE_H
