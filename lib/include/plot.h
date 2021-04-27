//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_PLOT_H
#define STATE_MACHINE_CPP_LIB_PLOT_H

#include <string>

namespace state_machine_cpp {
    namespace Algorithm {
        class Instance;
        void plot(const Algorithm::Instance &t_algorithm, const std::string &t_filename, bool t_run_command = true);
    }
}

#endif //STATE_MACHINE_CPP_LIB_PLOT_H
