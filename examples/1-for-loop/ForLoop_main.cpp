//
// Created by henri on 22/04/21.
//
#include <iostream>
#include "ForLoop_algorithm.h"

int main() {

    Algorithm::Instance algorithm;
    Algorithm::build<Counter>(algorithm);

    Algorithm::sanity_check(algorithm);
    Algorithm::plot(algorithm, "my_file");

    CounterAttributes counter_attributes(10);
    SimpleContext<CounterAttributes> context(counter_attributes);

    Algorithm::run(algorithm, context, INITIAL_STATE, FINAL_STATE);


    return 0;
}
