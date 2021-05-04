//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP___UNORDERED_MAP_H
#define STATE_MACHINE_CPP___UNORDERED_MAP_H

#ifdef USE_ROBIN_HOOD_UNORDERED_MAP

#include <robin_hood/robin_hood.h>
namespace state_machine_cpp {
    namespace unordered = robin_hood;
}

#else

#include <unordered_map>
#include <unordered_set>
namespace state_machine_cpp {
    namespace unordered = std;
}

#endif

#endif //STATE_MACHINE_CPP___UNORDERED_MAP_H
