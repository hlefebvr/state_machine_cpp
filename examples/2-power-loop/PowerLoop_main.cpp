//
// Created by henri on 25/04/21.
//

#include <iostream>
#include <complex>
#include "../1-for-loop/ForLoop_algorithm.h"

struct PowerLoopAttributes {
    unsigned int power;
    explicit PowerLoopAttributes(unsigned int t_power) : power(t_power) {}
};

void compute_power(Context& context) {
    const unsigned int i = context.get<CounterAttributes>().iteration;
    const double power = context.get<PowerLoopAttributes>().power;
    std::cout << i << "^" << power << " = " << std::pow(i, power) << std::endl;
}

class PowerLoop : public Algorithm::Builder {
public:

    void build(States &states, Transitions &transitions, Layers& layers) override {

        inherit<Counter>(states, transitions, layers);

        transitions.override(SHOW_COUNTER, INCREMENT_COUNTER, compute_power);

    }
};

int main(int argc, const char** argv) {

    Algorithm::Instance algorithm;

    CounterAttributes counter_attributes(6);
    PowerLoopAttributes power_attributes(2);
    SimpleContext<CounterAttributes, PowerLoopAttributes> context(counter_attributes, power_attributes);

    Algorithm::build<PowerLoop>(algorithm);
    Algorithm::sanity_check(algorithm);

    Algorithm::plot(algorithm, "power_loop");

    Algorithm::run(algorithm, context, INITIAL_STATE, FINAL_STATE);

    return 0;
}