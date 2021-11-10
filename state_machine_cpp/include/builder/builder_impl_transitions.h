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

    // HANDLER CREATORS
    std::function<int(Context2&)> create_parallelized_handler(const State::Instance &t_initial_state,
                                                             const std::vector<State::Instance>& t_next_states,
                                                             const State::Any &t_final_state);
    std::function<int(Context2&)> create_direct_handler(const State::Instance &t_initial_state,
                                                       Transition::TrivialHandler *t_handler);
    std::function<int(Context2&)> create_conditional_handler(const State::Instance &t_initial_state,
                                                            Transition::ConditionalHandler *t_handler);

    std::function<int(Context2&)> wrap_with_logs(const State::Instance& t_initial_state,
                                                std::function<int(Context2&)>&& t_function);

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
    Transitions(Algorithm::Instance& t_destination,
                const state_machine_cpp::Algorithm::Builder::Layers* t_layer,
                Algorithm::Mode t_build_mode);

    void remove(const State::Any &t_state) override;
    void declare_as_final(const State::Any &t_state) override;
};


#endif //STATE_MACHINE_CPP_BUILDER_IMPL_TRANSITIONS_H
