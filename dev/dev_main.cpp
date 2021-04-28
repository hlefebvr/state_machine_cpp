//
// Created by henri on 27/04/21.
//

#include <iostream>
#include "../lib/include/basics.h"

using namespace state_machine_cpp;

static const State::Id A("A");
static const State::Id B("B");
static const State::Id C("C");
static const State::Id D("D");
static const State::Id E("E");


class Builder1 final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) override {
        states.create(A);
        states.create(B);
        transitions.create(A, B);
        transitions.create(B, B);
    }
};

class Builder2 final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) override {
        states.create(C);
        states.create(D);
        states.create(E);
        transitions.create(C, D);
        transitions.create(D, E);
        transitions.create(E, E);
    }
};

class Builder3 final : public Algorithm::Builder {
public:
    void build(States& states, Transitions& transitions, Layers& layers) override {
        inherit<Builder1>(states, transitions, layers);

    }
};

int main(int argc, const char** argv) {


    Algorithm::Instance algorithm;
    Algorithm::build<Builder3>(algorithm);
    Algorithm::plot(algorithm, "my_algorithm_tx");
    Algorithm::sanity_check(algorithm);

    SimpleContext<bool> context;

    Algorithm::run(algorithm, context, A, B);

    return 0;
}
