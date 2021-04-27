//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_STATE_ANY_H
#define STATE_MACHINE_CPP_STATE_ANY_H

#include "state_instance.h"

namespace state_machine_cpp {
    template<class> class hash;

    namespace State {
        class Any;
    }
}


class state_machine_cpp::State::Any {
    State::Instance m_instance;
    bool m_is_instantiated;

    bool is_instantiated() const { return m_is_instantiated; }
    const State::Instance& as_provided() const { return m_instance; }
    State::Instance instantiate(unsigned int t_layer) const { return m_instance.id()[t_layer]; }
public:
    Any(const State::Id& t_id) // NOLINT(google-explicit-constructor)
            : m_instance(t_id), m_is_instantiated(false) {}
    Any(const State::Instance& t_instance) // NOLINT(google-explicit-constructor)
            : m_instance(t_instance), m_is_instantiated(true) {}

    State::Instance as_instance(unsigned int t_layer_if_not_set) const;
};


#endif //STATE_MACHINE_CPP_STATE_ANY_H
