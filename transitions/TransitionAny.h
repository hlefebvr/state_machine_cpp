//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITIONANY_H
#define STATE_MACHINE_CPP_TRANSITIONANY_H

#include <memory>

#include "../states/StateInstance.h"
#include "../states/hash.h"
#include "TransitionHandlerAny.h"

namespace Transition {
    class Any;
}

class Transition::Any {
    const State::Instance m_initial_state;
    std::unique_ptr<Transition::Handler::Any> m_handler;
public:
    Any(const State::Instance& t_initial_state); // NOLINT(google-explicit-constructor)

    const State::Instance& initial_state() const { return m_initial_state; }
    const State::Instance& operator()(Context& t_context) const;

    void set_handler(Transition::Handler::Any* t_handler);
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
