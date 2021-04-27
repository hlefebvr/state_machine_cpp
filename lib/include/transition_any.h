//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITION_ANY_H
#define STATE_MACHINE_CPP_TRANSITION_ANY_H

#include <memory>
#include <list>
#include <functional>

#include "state.h"
#include "__hash.h"

#include <vector>

namespace state_machine_cpp {
    class Context;
    namespace Transition {
        class Any;
    }
}

class state_machine_cpp::Transition::Any {
    const State::Instance m_initial_state;
    std::function<int(Context&)> m_function {};
    std::vector<State::Instance> m_next_states;
    bool m_is_final = false;
public:
    Any(const State::Instance& t_initial_state); // NOLINT(google-explicit-constructor)

    const State::Instance& initial_state() const { return m_initial_state; }
    std::vector<State::Instance> next_states() const;
    const State::Instance& operator()(Context& t_context) const;

    void set_handler(std::vector<State::Instance>&& t_next_states, std::function<int(Context&)>&& t_handler);
    void reset_handler();
    void set_as_final();
    bool has_handler() const;
    bool is_final() const;

    struct by_hash {

        long unsigned int operator()(const Any& t_x) const {
            return hash<State::Instance>::get(t_x.initial_state());
        }

        bool operator()(const Any& t_a, const Any& t_b) const {
            return t_a.initial_state() == t_b.initial_state();
        }
    };
};


#endif //STATE_MACHINE_CPP_TRANSITION_ANY_H
