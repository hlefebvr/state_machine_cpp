//
// Created by henri on 10/05/21.
//

#define STATE_MACHINE_CPP_EXAMPLE_FORLOOP_H
#include "../1_ForLoop/example_ForLoop_main.cpp"

class DoubleLoop final : public Algorithm::Builder {
public:

    static const State::Id& INITIAL_STATE;
    static const State::Id& FINAL_STATE;

    static void show_double_counter(Context& context) {
        const auto& i = context.get_relative<ForLoop::Attributes>(-1);
        const auto& j = context.get<ForLoop::Attributes>();
        std::cout << i.iteration << ", " << j.iteration << std::endl;
    }

    void build(States &states, Transitions &transitions, Layers &layers) override {
        import<ForLoop>(states, transitions, layers);

        auto A = layers.create();
            import<ForLoop>(states, transitions, layers);
            transitions.override(ForLoop::BEGIN_OF_ITERATION, ForLoop::END_OF_ITERATION, show_double_counter);
        layers.close();

        transitions.override(ForLoop::BEGIN_OF_ITERATION, INITIAL_STATE[A]);
        transitions.override(FINAL_STATE[A], ForLoop::END_OF_ITERATION);
    }

    static ContextTree<Layer<ForLoop::Attributes>, Layer<ForLoop::Attributes>>
    handle_standard_arguments(int n, int m) {
        return {
            new Layer(new ForLoop::Attributes(n)),
            new Layer(new ForLoop::Attributes(m))
        };
    }
};

const State::Id& DoubleLoop::INITIAL_STATE = ForLoop::INITIAL_STATE;
const State::Id& DoubleLoop::FINAL_STATE = ForLoop::FINAL_STATE;

int main(int argc, const char** argv) {

    Algorithm::Instance algorithm;
    Algorithm::build<DoubleLoop>(algorithm);
    Algorithm::sanity_check(algorithm);
    //Algorithm::plot(algorithm, "my_algorithm_merged");

    auto context_tree = DoubleLoop::handle_standard_arguments(3, 5);
    Context context(context_tree);

    Algorithm::run(algorithm, context);

    return 0;
}
