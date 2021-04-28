//
// Created by henri on 27/04/21.
//

#include <iostream>
#include "../lib/include/basics.h"

using namespace state_machine_cpp;

static const State::Id INITIAL_STATE("INITIAL_STATE");
static const State::Id LOOP_HAS_STARTED("LOOP_HAS_STARTED");
static const State::Id FINAL_STATE("FINAL_STATE");
static const State::Id LOOP_ITERATION("LOOP_ITERATION");
static const State::Id AFTER_LOOP_ITERATION("AFTER_LOOP_ITERATION");

struct ForLoopAttributes {
    int iteration = 0;
    int max_iteration;
    explicit ForLoopAttributes(int t_max_iteration) : max_iteration(t_max_iteration) {}
};

void handle_FINAL_STATE(Context& context) {
    std::cout << "the loop is over" << std::endl;
}

void handle_INITIAL_STATE(Context& context) {
    auto& for_loop_attributes = context.get<ForLoopAttributes>();
    for_loop_attributes.iteration = 0;
}

bool handle_LOOP_HAS_STARTED(const Context& context) {
    auto& for_loop_attributes = context.get<ForLoopAttributes>();
    return for_loop_attributes.iteration < for_loop_attributes.max_iteration;
}

void handle_LOOP_ITERATION(Context& context) {
    std::cout << context.get<ForLoopAttributes>().iteration << std::endl;
}

void handle_AFTER_LOOP_ITERATION(Context& context) {
    context.get<ForLoopAttributes>().iteration++;
}

class ForLoop final : public Algorithm::Builder {
public:

    void build(States& states, Transitions& transitions, Layers& layers) override {

        states.create(INITIAL_STATE);
        states.create(FINAL_STATE);
        states.create(LOOP_ITERATION);
        states.create(LOOP_HAS_STARTED);
        states.create(AFTER_LOOP_ITERATION);

        transitions.create(INITIAL_STATE, LOOP_HAS_STARTED, handle_INITIAL_STATE);
        transitions.create_if(LOOP_HAS_STARTED, LOOP_ITERATION, FINAL_STATE, handle_LOOP_HAS_STARTED);
        transitions.create(LOOP_ITERATION, AFTER_LOOP_ITERATION, handle_LOOP_ITERATION);
        transitions.create(AFTER_LOOP_ITERATION, LOOP_HAS_STARTED, handle_AFTER_LOOP_ITERATION);
        transitions.create(FINAL_STATE, FINAL_STATE, handle_FINAL_STATE);

    }

};

int main(int argc, const char** argv) {


    Algorithm::Instance algorithm;
    Algorithm::build<ForLoop>(algorithm);
    Algorithm::plot(algorithm, "my_algorithm_tx");
    Algorithm::sanity_check(algorithm);

    ForLoopAttributes attributes(10);
    SimpleContext<ForLoopAttributes> context(attributes);

    Algorithm::run(algorithm, context, INITIAL_STATE, FINAL_STATE);

    return 0;
}
