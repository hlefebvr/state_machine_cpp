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

    const auto node_style = [&t_algorithm](const Transition::Any& t_x) {
        std::stringstream style;
        style << "[label=\"" << t_x.initial_state().name() << "\",style=filled";
        switch (t_x.type()) {
            case Transition::Type::Conditional:
                style << ",shape=\"hexagon\",fillcolor=\"lightblue\"";
                break;
            case Transition::Type::Parallelized: [[fallthrough]];
            case Transition::Type::Undefined: [[fallthrough]];
            case Transition::Type::Direct:
                style << ",shape=\"box\",fillcolor=\"aliceblue\"";
                break;
        }
        if (t_algorithm.is_initial_state_set() && t_x.initial_state() == t_algorithm.initial_state()) {
            style << ",fillcolor=\"greenyellow\"";
        }
        if (t_algorithm.is_final_state_set() && t_x.initial_state() == t_algorithm.final_state()) {
            style << ",fillcolor=\"pink\"";
        }
        style << ']';
        return style.str();
    };

    const auto transition_style = [](const Transition::Any& t_transition, unsigned int t_index) {
        std::string color = "black";
        std::string label = " " + t_transition.description();
        std::string style = "solid";
        switch (t_transition.type()) {
            case Transition::Type::Undefined:
                throw std::runtime_error("Unexpected undefined transition when plotting.");
            case Transition::Type::Parallelized:
                color = "green";
                label += (t_index != 0 ? " async" : "");
                style = t_index == t_transition.next_states().size() - 1 ? "dashed" : style;
                break;
            case Transition::Type::Direct: break;
            case Transition::Type::Conditional:
                label += (t_index == 0 ? " = false" : " = true");
                break;
        }
        if (t_transition.is_virtual()) {
            color = "blue";
            label = "virtual";
        }
        if (t_transition.is_final()) {
            color = "red";
        }
        return "[style=\"" + style + "\",label=\"" + label + "\", color=\"" + color + "\",fontsize=10,fontcolor=darkgreen]";
    };

    std::ofstream file(t_filename + ".dot");

    if (!file.is_open()) {
        throw std::runtime_error("Could not open destination file");
    }

    file << "digraph G {";

    file << "\n\trankdir=TB;";

    file << "\n\n\t// state definitions\n";
    if (t_algorithm.is_initial_state_set()) {
        file << "\t"
             << name(t_algorithm.initial_state())
             << node_style(t_algorithm.transitions()[t_algorithm.initial_state()])
             << ";\n";
    }
    for (const auto& transition : t_algorithm.transitions()) {
        if ((t_algorithm.is_initial_state_set() && transition.initial_state() == t_algorithm.initial_state())
            || (t_algorithm.is_final_state_set() && transition.initial_state() == t_algorithm.final_state())) {
            continue;
        }
        file << "\t"
             << name(transition.initial_state())
             << node_style(transition)
             << ";\n";
    }
    if (t_algorithm.is_final_state_set()) {
        file << "\t"
             << name(t_algorithm.final_state())
             << node_style(t_algorithm.transitions()[t_algorithm.final_state()])
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
