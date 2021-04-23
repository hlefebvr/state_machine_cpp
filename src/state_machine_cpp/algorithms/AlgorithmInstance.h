//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_ALGORITHMINSTANCE_H
#define STATE_MACHINE_CPP_ALGORITHMINSTANCE_H

#include <robin_hood/robin_hood.h>

#include "Builder.h"
#include "../transitions/TransitionAny.h"

namespace Algorithm {
    class Instance;
    namespace Impl {
        namespace Build {
            class States;
            class Transitions;
        }
    }
}

class Algorithm::Instance {

    template<class T> using Set = robin_hood::unordered_set<T, typename T::by_hash, typename T::by_hash>;

    Set<Transition::Any> m_transitions;

    bool has(const State::Instance& t_instance) const;
    const State::Instance& apply_transition(const State::Instance& t_instance, Context& t_context) const;

    friend class Algorithm::Impl::Build::States;
    void create_state(const State::Instance& t_instance);
    void remove_state(const State::Instance& t_instance);

    friend class Algorithm::Impl::Build::Transitions;
    void create_any_transition(const State::Instance& t_initial_instance,
                               std::vector<State::Instance> &&t_next_states,
                               std::function<int(Context&)>&& t_handler,
                               bool t_should_already_exist);
    void create_transition(const State::Instance& t_initial_instance,
                           const State::Instance& t_next_instance,
                           Transition::TrivialHandler* t_handler,
                           bool t_should_already_exist);
    void create_transition_if(const State::Instance& t_initial_instance,
                           const State::Instance& t_if_instance,
                           const State::Instance& t_else_instance,
                           Transition::ConditionalHandler* t_handler,
                           bool t_should_already_exist);
    void remove_transition(const State::Instance& t_instance);
public:
    void run(Context& t_context, const State::Id& t_initial_state, const State::Id& t_final_state) const;

    const Set<Transition::Any>& transitions() const;
};


#endif //STATE_MACHINE_CPP_ALGORITHMINSTANCE_H
