//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_ALGORITHM_H
#define STATE_MACHINE_CPP_ALGORITHM_H

#include <robin_hood/robin_hood.h>
#include <stack>

#include "builder.h"
#include "transition.h"

namespace state_machine_cpp {
    namespace Algorithm {
        class Instance;
        namespace Impl {
            namespace Build {
                class States;
                class Transitions;
                class Layers;
            }
        }
    }
}

class state_machine_cpp::Algorithm::Instance {

    template<class T> using Set = robin_hood::unordered_set<T, typename T::by_hash, typename T::by_hash>;

    Set<Transition::Any> m_transitions;

    bool has(const State::Instance& t_instance) const;

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
    void set_as_final(const State::Instance& t_instance);
public:
    const Set<Transition::Any>& transitions() const;
};

#endif //STATE_MACHINE_CPP_ALGORITHM_H
