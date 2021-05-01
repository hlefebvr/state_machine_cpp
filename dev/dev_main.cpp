//
// Created by henri on 27/04/21.
//

#include <iostream>
#include "../lib/include/basics.h"

using namespace state_machine_cpp;

class MyAlgorithm : public Algorithm::Builder {
public:
    static const State::Id INITIAL_STATE;
    static const State::Id FINAL_STATE;

    static void handle_transition(Context& context) {
        std::cout << "HANDLED" << std::endl;
    }

    void build(States &states, Transitions &transitions, Layers &layers) override {

        states.create(INITIAL_STATE);
        states.create(FINAL_STATE);

        transitions.create(INITIAL_STATE, FINAL_STATE, handle_transition);
        transitions.create(FINAL_STATE, FINAL_STATE);

    }
};

const State::Id MyAlgorithm::INITIAL_STATE = State::Id("INITIAL_STATE");
const State::Id MyAlgorithm::FINAL_STATE = State::Id("FINAL_STATE");

int main(int argc, const char** argv) {


    Algorithm::Instance algorithm;
    Algorithm::build<MyAlgorithm>(algorithm);
    Algorithm::plot(algorithm, "my_algorithm_tx");
    Algorithm::sanity_check(algorithm);

    SimpleContext<bool> context;

    Algorithm::run_with_logs(algorithm, context, MyAlgorithm::INITIAL_STATE, MyAlgorithm::FINAL_STATE);

    return 0;
}
