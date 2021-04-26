//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_BUILDER_STATES_H
#define STATE_MACHINE_CPP_LIB_BUILDER_STATES_H

#include "Builder.h"

namespace Algorithm {
    namespace Impl {
        namespace Build {
            class States;
        }
    }
}

class Algorithm::Impl::Build::States : public Algorithm::Builder::States {
    Algorithm::Instance& m_destination;
public:
    States(Algorithm::Instance& t_destination, unsigned int t_level);

    void create(const State::Any& t_state) override;
    void remove(const State::Any& t_state) override;
};


#endif //STATE_MACHINE_CPP_LIB_BUILDER_STATES_H
