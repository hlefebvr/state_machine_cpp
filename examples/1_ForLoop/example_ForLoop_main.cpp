//
// Created by henri on 10/05/21.
//

#include <iostream>
#include "basics.h"

using namespace state_machine_cpp;

class ForLoop final : public Algorithm::Builder {
public:

    struct Attributes {
        int iteration = 0;
        int max_iteration;
        explicit Attributes(int max_iteration) : max_iteration(max_iteration) {}
    };

    static AttributeTree<Layer<ForLoop::Attributes>>* create_attributes(int max_iteration) {
        return new AttributeTree<Layer<ForLoop::Attributes>>(new Layer(new Attributes(max_iteration)));
    }

    static const State::Id INITIAL_STATE;
    static const State::Id LOOP_CONDITION_EVALUATION;
    static const State::Id BEGIN_OF_ITERATION;
    static const State::Id END_OF_ITERATION;
    static const State::Id FINAL_STATE;

    static void print_end_of_loop(Context& context) {
        std::cout << "The loop is over" << std::endl;
    }

    static void initialize_counter(Context& context) {
        auto& attributes = context.get<Attributes>();
        attributes.iteration = 0;
    }

    static bool evaluate_loop_condition(const Context& context) {
        auto& attributes = context.get<Attributes>();
        return attributes.iteration < attributes.max_iteration;
    }

    static void apply_loop_effect(Context& context) {
        std::cout << context.get<Attributes>().iteration << std::endl;
    }

    static void increment_counter(Context& context) {
        context.get<Attributes>().iteration++;
    }

    void build(States &states, Transitions &transitions, Layers &layers) override {

        states.create(INITIAL_STATE);
        states.create(LOOP_CONDITION_EVALUATION);
        states.create(BEGIN_OF_ITERATION);
        states.create(END_OF_ITERATION);
        states.create(FINAL_STATE);

        transitions.create(INITIAL_STATE, LOOP_CONDITION_EVALUATION, initialize_counter);
        transitions.create_if(LOOP_CONDITION_EVALUATION, BEGIN_OF_ITERATION, FINAL_STATE,evaluate_loop_condition);
        transitions.create(BEGIN_OF_ITERATION, END_OF_ITERATION, apply_loop_effect);
        transitions.create(END_OF_ITERATION, LOOP_CONDITION_EVALUATION, increment_counter);
        transitions.create(FINAL_STATE, FINAL_STATE, print_end_of_loop);

    }

};

const State::Id ForLoop::INITIAL_STATE = State::Id("ForLoop::INITIAL_STATE");
const State::Id ForLoop::LOOP_CONDITION_EVALUATION = State::Id("ForLoop::LOOP_CONDITION_EVALUATION");
const State::Id ForLoop::BEGIN_OF_ITERATION = State::Id("ForLoop::BEGIN_OF_ITERATION");
const State::Id ForLoop::END_OF_ITERATION = State::Id("ForLoop::END_OF_ITERATION");
const State::Id ForLoop::FINAL_STATE = State::Id("ForLoop::FINAL_STATE");

#ifndef STATE_MACHINE_CPP_EXAMPLE_FORLOOP_H

int main() {

    Algorithm::Instance algorithm;
    Algorithm::build<ForLoop>(algorithm);
    Algorithm::plot(algorithm, "my_algorithm", false);
    Algorithm::sanity_check(algorithm);

    //auto context_tree = ForLoop::create_attributes(10);
    //Context context(context_tree);
    auto context = Context::create<ForLoop>(10);

    Algorithm::run(algorithm, context);

    return 0;
}

#endif // STATE_MACHINE_CPP_EXAMPLE_FORLOOP_H