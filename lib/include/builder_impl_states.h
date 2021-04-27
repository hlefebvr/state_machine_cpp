//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_IMPL_STATES_H
#define STATE_MACHINE_CPP_BUILDER_IMPL_STATES_H

#include "builder_states.h"

namespace state_machine_cpp {
    namespace Algorithm {
        class Instance;
        namespace Impl {
            namespace Build {
                class States;
            }
        }
    }
}

class state_machine_cpp::Algorithm::Impl::Build::States : public state_machine_cpp::Algorithm::Builder::States {
    Algorithm::Instance& m_destination;
public:
    States(Algorithm::Instance& t_destination, const state_machine_cpp::Algorithm::Builder::Layers* t_layer);

    void create(const State::Any& t_state) override;
    void remove(const State::Any& t_state) override;
};


#endif //STATE_MACHINE_CPP_BUILDER_IMPL_STATES_H
