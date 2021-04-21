#include <iostream>

#include "states/hash.h"
#include "states/StateId.h"

static const State::Id INITIAL_STATE("INITIAL_STATE");
static const State::Id FINAL_STATE("FINAL_STATE");

int main() {

    std::cout << (INITIAL_STATE[1] == INITIAL_STATE[1]) << std::endl;
    std::cout << hash<State::Instance>::get(FINAL_STATE[1]) << std::endl;

    return 0;
}
