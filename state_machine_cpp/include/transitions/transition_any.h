//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_TRANSITION_ANY_H
#define STATE_MACHINE_CPP_TRANSITION_ANY_H

#include <list>
#include <functional>
#include <vector>

#include "states/state_any.h"
#include "impl/__hash.h"
#include "transition_handlers.h"

namespace state_machine_cpp {
    class Context;
    namespace Transition {
        class Any;
    }
}

class state_machine_cpp::Transition::Any {
    const State::Instance m_initial_state;
    std::function<int(Context2&)> m_function {};
    std::vector<State::Instance> m_next_states;
    Type m_type = Transition::Type::Undefined;
    bool m_is_final = false;
public:
    Any(const State::Instance& t_initial_state); // NOLINT(google-explicit-constructor)

    [[nodiscard]] const State::Instance& initial_state() const { return m_initial_state; }
    [[nodiscard]] std::vector<State::Instance> next_states() const;
    const State::Instance& operator()(Context2& t_context) const;

    void set_handler(Transition::Type t_transition_type, std::vector<State::Instance>&& t_next_states, std::function<int(Context2&)>&& t_handler);
    void reset_handler();
    void set_as_final();

    [[nodiscard]] bool has_handler() const;
    [[nodiscard]] bool is_final() const;
    [[nodiscard]] bool is_virtual() const;
    [[nodiscard]] Type type() const;

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
