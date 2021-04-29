//
// Created by henri on 27/04/21.
//

#include <iostream>
#include "../1-for-loop/ForLoop_algorithm.h"

void show_double_counter(Context& context) {
    std::cout << context.get_relative<CounterAttributes>(-1).iteration
              << ", "
              << context.get<CounterAttributes>().iteration
              << std::endl;
}

class DoubleLoop : public Algorithm::Builder {
public:
    void build(States &states, Transitions &transitions, Layers &layers) override {
        inherit<Counter>(states, transitions, layers);

        unsigned int A = layers.create();
        inherit<Counter>(states, transitions, layers);
        transitions.override(SHOW_COUNTER, INCREMENT_COUNTER, show_double_counter);
        layers.close();

        transitions.override(SHOW_COUNTER, INITIAL_STATE[A]);
        transitions.override(FINAL_STATE[A], INCREMENT_COUNTER);

    }
};

int main(int argc, const char** argv) {

    Algorithm::Instance algorithm;
    Algorithm::build<DoubleLoop>(algorithm);

    Algorithm::sanity_check(algorithm);
    Algorithm::plot(algorithm, "my_file");

    CounterAttributes counter_attributes(3);
    CounterAttributes counter_attributes_2(5);
    SimpleContext<CounterAttributes> context(counter_attributes);
    SimpleContext<CounterAttributes> context_2(counter_attributes_2);
    LayeredContext<2> layered_context(context, context_2);

    Algorithm::run(algorithm, layered_context, INITIAL_STATE, FINAL_STATE);

    return 0;
}
