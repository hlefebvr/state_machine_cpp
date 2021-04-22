//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_PLOT_H
#define STATE_MACHINE_CPP_LIB_PLOT_H

#include "AlgorithmTransitionsPlotter.h"
#include "AlgorithmStatePlotter.h"

namespace Algorithm {
    template<class T> void plot();
}

template<class T>
void Algorithm::plot() {
    Impl::Plot::States states(0);
    Impl::Plot::Transitions transitions(0);

    T builder;
    builder.build(states, transitions);
}

#endif //STATE_MACHINE_CPP_LIB_PLOT_H
