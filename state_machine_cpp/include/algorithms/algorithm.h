//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_ALGORITHM_H
#define STATE_MACHINE_CPP_ALGORITHM_H

#include <stack>

#include "transitions/transition_any.h"
#include "transitions/transition_handlers.h"
#include "impl/__map.h"

namespace state_machine_cpp::Algorithm {
    class Instance;
    namespace Impl::Build {
            class States;
            class Transitions;
            class Layers;
        }
    }

class state_machine_cpp::Algorithm::Instance {

    TransitionSet m_transitions;
    const State::Id* m_initial_state = nullptr;
    const State::Id* m_final_state = nullptr;
    const State::Id* m_time_limit_state = nullptr;

    [[nodiscard]] bool has(const State::Instance& t_instance) const;

    friend class Algorithm::Impl::Build::States;
    void create_state(const State::Instance& t_instance);
    void remove_state(const State::Instance& t_instance);

    friend class Algorithm::Impl::Build::Transitions;
    void create_any_transition(const State::Instance& t_initial_instance,
                               Transition::Type t_transition_type,
                               std::vector<State::Instance> &&t_next_states,
                               std::function<int(Context&)>&& t_handler,
                               bool t_is_override,
                               std::string&& t_description);
    void remove_transition(const State::Instance& t_instance);
    void set_as_final(const State::Instance& t_instance);
public:
    [[nodiscard]] const TransitionSet& transitions() const;

    [[nodiscard]] inline const State::Id& initial_state() const;
    [[nodiscard]] inline const State::Id& final_state() const;
    [[nodiscard]] inline const State::Id& time_limit_reached_state() const;
    [[nodiscard]] inline bool is_initial_state_set() const;
    [[nodiscard]] inline bool is_final_state_set() const;
    inline void set_initial_state(const State::Id& t_initial_state);
    inline void set_final_state(const State::Id& t_final_state);
    inline void set_time_limit_reached_state(const State::Id& t_time_limit_reached);
};

const state_machine_cpp::State::Id &state_machine_cpp::Algorithm::Instance::initial_state() const {
    if (!m_initial_state) {
        throw std::runtime_error("No initial state configure. Use set_initial_state.");
    }
    return *m_initial_state;
}

const state_machine_cpp::State::Id &state_machine_cpp::Algorithm::Instance::final_state() const {
    if (!m_final_state) {
        throw std::runtime_error("No initial state configure. Use set_initial_state.");
    }
    return *m_final_state;
}

bool state_machine_cpp::Algorithm::Instance::is_initial_state_set() const {
    return m_initial_state;
}

bool state_machine_cpp::Algorithm::Instance::is_final_state_set() const {
    return m_final_state;
}

void state_machine_cpp::Algorithm::Instance::set_initial_state(const state_machine_cpp::State::Id &t_initial_state) {
    m_initial_state = &t_initial_state;
}

void state_machine_cpp::Algorithm::Instance::set_final_state(const state_machine_cpp::State::Id &t_final_state) {
    m_final_state = &t_final_state;
}

void state_machine_cpp::Algorithm::Instance::set_time_limit_reached_state(
        const state_machine_cpp::State::Id &t_time_limit_reached) {
    m_time_limit_state = &t_time_limit_reached;
}

const state_machine_cpp::State::Id &state_machine_cpp::Algorithm::Instance::time_limit_reached_state() const {
    return m_time_limit_state ? *m_time_limit_state : *m_final_state;
}


#endif //STATE_MACHINE_CPP_ALGORITHM_H
