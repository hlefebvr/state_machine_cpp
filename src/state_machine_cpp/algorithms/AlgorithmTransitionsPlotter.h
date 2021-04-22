//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_ALGORITHMTRANSITIONSPLOTTER_H
#define STATE_MACHINE_CPP_LIB_ALGORITHMTRANSITIONSPLOTTER_H

#include "AlgorithmBuilder.h"

namespace Algorithm {
    namespace Impl {
        namespace Plot {
            class Transitions;
        }
    }
}


class Algorithm::Impl::Plot::Transitions : public Algorithm::Builder::Transitions{
public:
    explicit Transitions(unsigned int t_level);

    void remove(const State::Any &t_state) override;

private:
    void create_or_override(bool t_do_override,
                            const State::Any &t_initial_state,
                            const State::Any &t_next_state,
                            Transition::TrivialHandler & t_handler) override;

    void create_or_override_if(bool t_do_override,
                               const State::Any &t_initial_state,
                               const State::Any &t_if_true,
                               const State::Any &t_else,
                               Transition::ConditionalHandler & t_handler) override;
};


#endif //STATE_MACHINE_CPP_LIB_ALGORITHMTRANSITIONSPLOTTER_H
