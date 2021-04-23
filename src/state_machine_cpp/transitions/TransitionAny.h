//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITIONANY_H
#define STATE_MACHINE_CPP_TRANSITIONANY_H

#include <memory>
#include <list>
#include <functional>

#include "../states/StateInstance.h"
#include "../states/hash.h"
#include "TransitionHandlerType.h"

#include <vector>

namespace Transition {
    class Any;
}

class Transition::Any {
    const State::Instance m_initial_state;
    std::function<int(Context&)> m_function {};
    std::vector<State::Instance> m_next_states;
public:
    Any(const State::Instance& t_initial_state); // NOLINT(google-explicit-constructor)

    const State::Instance& initial_state() const { return m_initial_state; }
    std::vector<State::Instance> next_states() const;
    const State::Instance& operator()(Context& t_context) const;

    void set_handler(std::vector<State::Instance>&& t_next_states, std::function<int(Context&)>&& t_handler);
    void reset_handler();
    bool has_handler() const;

    struct by_hash {

        long unsigned int operator()(const Any& t_x) const {
            return hash<State::Instance>::get(t_x.initial_state());
        }

        bool operator()(const Any& t_a, const Any& t_b) const {
            return t_a.initial_state() == t_b.initial_state();
        }
    };
};


#endif //STATE_MACHINE_CPP_TRANSITIONANY_H
