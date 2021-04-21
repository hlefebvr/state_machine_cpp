//
// Created by henri on 21/04/21.
//

#include "StateId.h"

#include <iostream>

State::Id::Id(const char *t_name) noexcept : m_name(t_name), m_hash(std::hash<std::string>()(t_name)) {}

std::ostream& operator<<(std::ostream& t_os, const State::Id& t_id) {
    return t_os << t_id.name();
}