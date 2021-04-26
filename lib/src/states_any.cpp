//
// Created by henri on 22/04/21.
//

#include "states.h"

State::Instance State::Any::as_instance(unsigned int t_level_if_not_set) const {
    return is_instantiated() ? as_provided() : instantiate(t_level_if_not_set);
}
