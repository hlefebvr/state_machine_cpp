//
// Created by henri on 22/04/21.
//
#include <iostream>

#include <state_machine_cpp/states/StateId.h>
#include <state_machine_cpp/context/Context.h>
#include <state_machine_cpp/algorithms/Builder.h>
#include <state_machine_cpp/algorithms/build.h>
#include <state_machine_cpp/context/InitialContext.h>
#include <state_machine_cpp/algorithms/AlgorithmInstance.h>
#include <state_machine_cpp/algorithms/plot.h>
#include <state_machine_cpp/algorithms/sanity_check.h>

static const State::Id INITIAL_STATE("INITIAL_STATE");
static const State::Id CHECK_IF_HAS_CONVERGED("CHECK_IF_HAS_CONVERGED");
static const State::Id SHOW_COUNTER("SHOW_COUNTER");
static const State::Id INCREMENT_COUNTER("INCREMENT_COUNTER");
static const State::Id FINAL_STATE("FINAL_STATE");

static const State::Id MY_STATE("MY_STATE");

struct CounterAttributes {
    unsigned int n = 0;
};

void initialize_attributes(Context& context) {
    context.get<CounterAttributes>().n = 0;
}

bool check_convergence(const Context& context) {
    return context.get<CounterAttributes>().n == 10;
}

void show_counter(Context& context) {
    std::cout << context.get<CounterAttributes>().n << std::endl;
}

void increment_counter(Context& context) {
    ++context.get<CounterAttributes>().n;
}

void do_nothing(Context& context) {}

struct Counter final : public Algorithm::Builder {

    void build(States& states, Transitions& transitions) override {

        states.create(INITIAL_STATE);
        states.create(CHECK_IF_HAS_CONVERGED);
        states.create(SHOW_COUNTER);
        states.create(INCREMENT_COUNTER);
        states.create(FINAL_STATE);

        states.create(MY_STATE);
        transitions.create_virtual(MY_STATE, FINAL_STATE);

        transitions.create(INITIAL_STATE, CHECK_IF_HAS_CONVERGED, initialize_attributes);
        transitions.create_if(CHECK_IF_HAS_CONVERGED, FINAL_STATE, SHOW_COUNTER, check_convergence);
        transitions.create(SHOW_COUNTER, INCREMENT_COUNTER, show_counter);
        transitions.create(INCREMENT_COUNTER, CHECK_IF_HAS_CONVERGED, increment_counter);
        transitions.create(FINAL_STATE, FINAL_STATE, do_nothing);

        transitions.declare_as_final(CHECK_IF_HAS_CONVERGED);

    }

};

int main() {

    Algorithm::Instance algorithm;
    Algorithm::build<Counter>(algorithm);

    Algorithm::sanity_check(algorithm);
    Algorithm::plot(algorithm, "my_file");

    CounterAttributes counter_attributes;
    InitialContext<CounterAttributes> context(counter_attributes);

    algorithm.run(context, INITIAL_STATE, FINAL_STATE);

    return 0;
}
