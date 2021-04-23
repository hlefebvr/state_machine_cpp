//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_PLOT_H
#define STATE_MACHINE_CPP_LIB_PLOT_H

#include <fstream>
#include <list>
#include <sstream>
#include "AlgorithmTransitionsPlotter.h"
#include "AlgorithmStatePlotter.h"

namespace Algorithm {
    template<class T> void plot(const std::string& t_filename, bool t_run_command = true);
}

template<class T>
void Algorithm::plot(const std::string& t_filename, bool t_run_command) {
    robin_hood::unordered_map<std::string, std::list<std::string>> store;

    Impl::Explorer::States states(store, 0);
    Impl::Explorer::Transitions transitions(store, 0);

    T builder;
    builder.build(states, transitions);

    const auto name = [](const std::string& t_org_name) {
        std::string result = t_org_name;
        std::replace(result.begin(), result.end(), '[', '_');
        std::replace(result.begin(), result.end(), ']', ' ');
        return result;
    };

    const auto node_style = [](bool t_is_trivial_transition) {
        if (t_is_trivial_transition) {
            return "[shape=\"oval\"]";
        }
        return "[shape=\"diamond\"]";
    };

    std::ofstream file(t_filename + ".dot");

    if (!file.is_open()) {
        throw std::runtime_error("Could not open destination file");
    }

    file << "digraph G {";

    file << "\n\n\t// state definitions\n";
    for (const auto& state_and_successors : store) {
        file << "\t"
             << name(state_and_successors.first)
             << node_style(state_and_successors.second.size() <= 1)
             << ";\n";
    }

    file << "\n\n\t// transition definition\n";
    for (const auto& state_and_successors : store) {
        for (const auto& next_state : state_and_successors.second) {
            file << "\t"
                 << name(state_and_successors.first)
                 << " -> "
                 << name(next_state)
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

#endif //STATE_MACHINE_CPP_LIB_PLOT_H
