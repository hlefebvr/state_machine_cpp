#include <iostream>

#include "states/hash.h"
#include "states/StateId.h"
#include "builder/Builder.h"
#include "builder/AlgorithmInstance.h"
#include "builder/build.h"

static const State::Id INITIAL_STATE("INITIAL_STATE");
static const State::Id IF_TRUE("IF_TRUE");
static const State::Id IF_FALSE("IF_FALSE");
static const State::Id FINAL_STATE("FINAL_STATE");

void handler() {
    std::cout << "HANDLE" << std::endl;
}

bool handler_if() { return true; }

struct Counter final : public Algorithm::Builder {

    void build(States& states, Transitions& transitions) override {

        states.create(INITIAL_STATE);
        states.remove(INITIAL_STATE);

        transitions.create(INITIAL_STATE, FINAL_STATE, handler);
        transitions.override(INITIAL_STATE, FINAL_STATE, handler);
        transitions.remove(INITIAL_STATE);

        transitions.create_if(INITIAL_STATE, IF_TRUE, IF_FALSE, handler_if);
        transitions.override_if(INITIAL_STATE, IF_TRUE, IF_FALSE, handler_if);

    }

};

int main() {

    Algorithm::Instance algorithm;

    Algorithm::build<Counter>(algorithm);

    return 0;
}
