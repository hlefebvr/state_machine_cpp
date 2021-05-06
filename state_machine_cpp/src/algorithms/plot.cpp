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
        std::string result = "node_" + std::to_string(hash<State::Instance>::get(t_x));
        std::replace(result.begin(), result.end(), '[', '_');
        std::replace(result.begin(), result.end(), ']', ' ');
        return result;
    };

    const auto node_style = [](const State::Instance& t_x, bool t_is_trivial_transition) {
        std::stringstream style;
        style << "[label=\"" << t_x.name() << "\"";
        if (t_is_trivial_transition) {
            style << ",shape=\"oval\"]";
        } else {
            style << ",shape=\"diamond\"]";
        }
        return style.str();
    };

    const auto transition_style = [](const Transition::Any& t_transition) {
        if (!t_transition.has_handler()) {
            return "[color=\"blue\",label=\"virtual\"]";
        }
        if (t_transition.is_final()) {
            return "[color=\"red\"]";
        }
        return "";
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
             << node_style(transition.initial_state(), transition.next_states().size() <= 1)
             << ";\n";
    }

    file << "\n\n\t// transition definition\n";
    for (const auto& transition : t_algorithm.transitions()) {
        for (const auto& next_state : transition.next_states()) {
            file << "\t"
                 << name(transition.initial_state())
                 << " -> "
                 << name(next_state)
                 << transition_style(transition)
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
