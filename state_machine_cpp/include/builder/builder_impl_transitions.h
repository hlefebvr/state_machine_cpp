//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_IMPL_TRANSITIONS_H
#define STATE_MACHINE_CPP_BUILDER_IMPL_TRANSITIONS_H

#include "builder_transitions.h"
#include "../states/state_any.h"
#include "../states/state_instance.h"
#include <list>
#include <functional>

namespace state_machine_cpp::Algorithm {
    class Instance;
    namespace Impl::Build {
        class Transitions;
    }
}

class state_machine_cpp::Algorithm::Impl::Build::Transitions : public Algorithm::Builder::Transitions {
protected:
    Algorithm::Instance& m_destination;

    // HANDLER CREATORS
    std::function<int(Context&)> create_parallelized_handler(const State::Any &t_initial_state,
                                                              const std::vector<State::Instance>& t_next_states,
                                                              const State::Any &t_final_state);
    std::function<int(Context&)> create_direct_handler(Transition::TrivialHandler *t_handler);
    std::function<int(Context&)> create_conditional_handler(Transition::ConditionalHandler *t_handler);

    // TRANSITION CREATORS
    void create_or_override(bool t_is_override,
                            const State::Any &t_initial_state,
                            const State::Any &t_next_state,
                            Transition::TrivialHandler *t_handler) override;
    void create_or_override_if(bool t_is_override,
                               const State::Any &t_initial_state,
                               const State::Any &t_if_true,
                               const State::Any &t_else,
                               Transition::ConditionalHandler *t_handler) override;
    void create_or_override_parallelized(bool t_is_override,
                                         const State::Any &t_initial_state,
                                         std::initializer_list<State::Any> t_next_states,
                                         const State::Any &t_final_state) override;

public:
    Transitions(Algorithm::Instance& t_destination, const state_machine_cpp::Algorithm::Builder::Layers* t_layer);

    void remove(const State::Any &t_state) override;
    void declare_as_final(const State::Any &t_state) override;
};


#endif //STATE_MACHINE_CPP_BUILDER_IMPL_TRANSITIONS_H
