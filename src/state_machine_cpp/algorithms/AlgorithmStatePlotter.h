//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_ALGORITHMSTATEPLOTTER_H
#define STATE_MACHINE_CPP_LIB_ALGORITHMSTATEPLOTTER_H

#include "AlgorithmBuilder.h"

namespace Algorithm {
    namespace Impl {
        namespace Plot {
            class States;
        }
    }
}

class Algorithm::Impl::Plot::States : public Algorithm::Builder::States {
public:
    explicit States(unsigned int t_level);

    void create(const State::Any& t_state) override;
    void remove(const State::Any& t_state) override;
};


#endif //STATE_MACHINE_CPP_LIB_ALGORITHMSTATEPLOTTER_H
