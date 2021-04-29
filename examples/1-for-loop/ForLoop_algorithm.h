//
// Created by henri on 25/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB__EXAMPLE_FOR_LOOP_H
#define STATE_MACHINE_CPP_LIB__EXAMPLE_FOR_LOOP_H

#include <state_machine_cpp/basics.h>

using namespace state_machine_cpp;

static const State::Id INITIAL_STATE("INITIAL_STATE");
static const State::Id CHECK_IF_HAS_CONVERGED("LOOP_HAS_STARTED");
static const State::Id SHOW_COUNTER("LOOP_ITERATION");
static const State::Id INCREMENT_COUNTER("AFTER_LOOP_ITERATION");
static const State::Id FINAL_STATE("FINAL_STATE");

struct CounterAttributes {
    const unsigned int max;
    unsigned int iteration = 0;
    explicit CounterAttributes(unsigned int t_max) : max(t_max) {}
};

void initialize_attributes(Context& context) {
    context.get<CounterAttributes>().iteration = 0;
}

bool check_convergence(const Context& context) {
    const auto& ctx = context.get<CounterAttributes>();
    return ctx.iteration >= ctx.max;
}

void show_counter(Context& context) {
    std::cout << context.get<CounterAttributes>().iteration << std::endl;
}

void increment_counter(Context& context) {
    ++context.get<CounterAttributes>().iteration;
}

struct Counter final : public Algorithm::Builder {

    void build(States& states, Transitions& transitions, Layers& layers) override {

        states.create(INITIAL_STATE);
        states.create(CHECK_IF_HAS_CONVERGED);
        states.create(SHOW_COUNTER);
        states.create(INCREMENT_COUNTER);
        states.create(FINAL_STATE);

        transitions.create(INITIAL_STATE, CHECK_IF_HAS_CONVERGED, initialize_attributes);
        transitions.create_if(CHECK_IF_HAS_CONVERGED, FINAL_STATE, SHOW_COUNTER, check_convergence);
        transitions.create(SHOW_COUNTER, INCREMENT_COUNTER, show_counter);
        transitions.create(INCREMENT_COUNTER, CHECK_IF_HAS_CONVERGED, increment_counter);
        transitions.create(FINAL_STATE, FINAL_STATE);

    }

};

#endif //STATE_MACHINE_CPP_LIB__EXAMPLE_FOR_LOOP_H
