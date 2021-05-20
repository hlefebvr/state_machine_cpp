//
// Created by henri on 10/05/21.
//

#include <complex>

#define STATE_MACHINE_CPP_EXAMPLE_FORLOOP_H
#include "../1_ForLoop/example_ForLoop_main.cpp"

class PowerLoop final : public Algorithm::Builder {
public:

    struct Attributes {
        unsigned int power;
        explicit Attributes(unsigned int power) : power(power) {}
    };

    static AutoContext handle_standard_arguments(int max_iteration, unsigned int power) {
        auto* for_loop_attributes = new ForLoop::Attributes(max_iteration);
        auto* power_loop_attributes = new PowerLoop::Attributes(power);
        auto* context = new SimpleContext<ForLoop::Attributes, PowerLoop::Attributes>(*for_loop_attributes, *power_loop_attributes);

        return AutoContext(context, for_loop_attributes, power_loop_attributes);
    }

    static const State::Id& INITIAL_STATE;
    static const State::Id& FINAL_STATE;

    static void print_power_of_iteration(Context& context) {
        auto& power_loop_attributes = context.get<PowerLoop::Attributes>();
        auto& for_loop_attributes = context.get<ForLoop::Attributes>();
        std::cout << for_loop_attributes.iteration << '^' << power_loop_attributes.power
                  << " = " << std::pow(for_loop_attributes.iteration, power_loop_attributes.power)
                  << std::endl;
    }

    void build(States &states, Transitions &transitions, Layers &layers) override {
        import<ForLoop>(states, transitions, layers);

        transitions.override(ForLoop::BEGIN_OF_ITERATION, ForLoop::END_OF_ITERATION, print_power_of_iteration);
    }
};

const State::Id& PowerLoop::INITIAL_STATE = ForLoop::INITIAL_STATE;
const State::Id& PowerLoop::FINAL_STATE = ForLoop::FINAL_STATE;

int main(int argc, const char** argv) {

    Algorithm::Instance algorithm;
    Algorithm::build<PowerLoop>(algorithm);
    Algorithm::sanity_check(algorithm);
    Algorithm::plot(algorithm, "my_algorithm");

    auto context = PowerLoop::handle_standard_arguments(3, 2);

    Algorithm::run(algorithm, context);

}