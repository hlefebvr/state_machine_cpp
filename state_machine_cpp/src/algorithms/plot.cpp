//
// Created by henri on 27/04/21.
//

#include <fstream>
#include <sstream>
#include <algorithm>

#include "algorithms/plot.h"
#include "states/state_instance.h"
#include "transitions/transition_any.h"
#include "algorithms/algorithm.h"

void state_machine_cpp::Algorithm::plot(const Algorithm::Instance& t_algorithm, const std::string& t_filename, bool t_run_command) {

    const auto name = [](const State::Instance& t_x) {
        return "node_" + std::to_string(hash<State::Instance>::get(t_x));
    };

    const auto node_style = [](const Transition::Any& t_x) {
        std::stringstream style;
        style << "[label=\"" << t_x.initial_state().name() << "\"";
        switch (t_x.type()) {
            case Transition::Type::Conditional:
                style << ",shape=\"diamond\"";
                break;
            case Transition::Type::Parallelized: [[fallthrough]];
            case Transition::Type::Undefined: [[fallthrough]];
            case Transition::Type::Direct:
                style << ",shape=\"oval\"";
                break;
        }
        style << ']';
        return style.str();
    };

    const auto transition_style = [](const Transition::Any& t_transition, unsigned int t_index) {
        std::string color = "black";
        std::string label;
        std::string style = "solid";
        switch (t_transition.type()) {
            case Transition::Type::Undefined:
                throw std::runtime_error("Unexpected undefined transition when plotting.");
            case Transition::Type::Parallelized:
                color = "green";
                label = t_index != 0 ? "async" : "";
                style = t_index == t_transition.next_states().size() - 1 ? "dashed" : style;
                break;
            case Transition::Type::Direct: break;
            case Transition::Type::Conditional:
                label = t_index == 0 ? "false" : "true";
                break;
        }
        if (t_transition.is_virtual()) {
            color = "blue";
            label = "virtual";
        }
        if (t_transition.is_final()) {
            color = "red";
        }
        return "[style=\"" + style + "\",label=\"" + label + "\", color=\"" + color + "\"]";
    };

    std::ofstream file(t_filename + ".dot");

    if (!file.is_open()) {
        throw std::runtime_error("Could not open destination file");
    }

    file << "digraph G {";

    file << "\n\n\t// state definitions\n";
    for (const auto& transition : t_algorithm.transitions()) {
        file << "\t"
             << name(transition.initial_state())
             << node_style(transition)
             << ";\n";
    }

    file << "\n\n\t// transition definition\n";
    for (const auto& transition : t_algorithm.transitions()) {
        const std::vector<State::Instance>& next_states = transition.next_states();
        for (unsigned int i = 0, n = next_states.size() ; i < n ; ++i) {
            file << "\t"
                 << name(transition.initial_state())
                 << " -> "
                 << name(next_states[i])
                 << transition_style(transition, i)
                 << ";\n";
        }
    }

    file << "\n}";

    file.close();

    if (t_run_command) {
        std::stringstream ss;
        ss << "dot -Tpng " << t_filename << ".dot -o " << t_filename << ".png"
           << " && xdg-open " << t_filename << ".png";
        system(ss.str().c_str());;
    }
}
