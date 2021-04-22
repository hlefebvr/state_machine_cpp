//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_STATEANY_H
#define STATE_MACHINE_CPP_STATEANY_H

#include "StateInstance.h"
#include "StateId.h"

namespace State {
    class Any;
}

namespace Algorithm {
    class Builder;
}

class State::Any {
    State::Instance m_instance;
    bool m_is_instantiated;

    bool is_instantiated() const { return m_is_instantiated; }
    const State::Instance& as_provided() const { return m_instance; }
    State::Instance instantiate(unsigned int t_level) const { return m_instance.id()[t_level]; }
public:
    Any(const State::Id& t_id) // NOLINT(google-explicit-constructor)
        : m_instance(t_id), m_is_instantiated(false) {}
    Any(const State::Instance& t_instance) // NOLINT(google-explicit-constructor)
        : m_instance(t_instance), m_is_instantiated(true) {}

    State::Instance as_instance(unsigned int t_level_if_not_set) const;
};

#endif //STATE_MACHINE_CPP_STATEANY_H
