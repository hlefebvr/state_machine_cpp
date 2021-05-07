//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_IMPL_TRANSITIONS_H
#define STATE_MACHINE_CPP_BUILDER_IMPL_TRANSITIONS_H

#include "builder_transitions.h"

namespace state_machine_cpp {
    namespace Algorithm {
        class Instance;
        namespace Impl {
            namespace Build {
                class Transitions;
            }
        }
    }
}

class state_machine_cpp::Algorithm::Impl::Build::Transitions : public Algorithm::Builder::Transitions {
protected:
    Algorithm::Instance& m_destination;

    void create_or_override(bool t_do_override,
                            const State::Any &t_initial_state,
                            const State::Any &t_next_state,
                            Transition::TrivialHandler *t_handler) override;
    void create_or_override_if(bool t_do_override,
                               const State::Any &t_initial_state,
                               const State::Any &t_if_true,
                               const State::Any &t_else,
                               Transition::ConditionalHandler *t_handler) override;
public:
    Transitions(Algorithm::Instance& t_destination, const state_machine_cpp::Algorithm::Builder::Layers* t_layer);

    void remove(const State::Any &t_state) override;

    void create_parallelized(const State::Any &t_initial_state, std::initializer_list<State::Any> t_next_states,
                             const State::Any &t_final_state) override;

    void declare_as_final(const State::Any &t_state) override;
};


#endif //STATE_MACHINE_CPP_BUILDER_IMPL_TRANSITIONS_H
