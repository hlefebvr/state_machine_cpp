//
// Created by henri on 22/04/21.
//

#include <states/state_any.h>

#include "states/state.h"

state_machine_cpp::State::Instance state_machine_cpp::State::Any::as_instance(unsigned int t_layer_if_not_set) const {
    return is_instantiated() ? as_provided() : instantiate(t_layer_if_not_set);
}

state_machine_cpp::State::Instance state_machine_cpp::State::Any::instantiate(unsigned int t_layer) const {
    return m_instance.id()[t_layer];
}
