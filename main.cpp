#include <iostream>

#include "states/StateId.h"

static const State::Id INITIAL_STATE("INITIAL_STATE");
static const State::Id FINAL_STATE("FINAL_STATE");

int main() {

    std::cout << (INITIAL_STATE[1] == INITIAL_STATE[1]) << std::endl;
    std::cout << FINAL_STATE[1] << std::endl;

    return 0;
}
