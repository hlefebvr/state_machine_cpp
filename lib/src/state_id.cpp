//
// Created by henri on 27/04/21.
//

#include "state_id.h"
#include "state_instance.h"

state_machine_cpp::State::Id::Id(const char *t_name) noexcept : m_name(t_name), m_hash(std::hash<std::string>()(t_name)) {}

state_machine_cpp::State::Instance state_machine_cpp::State::Id::operator[](unsigned int t_layer) const {
    return State::Instance(*this, t_layer);
}

std::ostream& operator<<(std::ostream& t_os, const state_machine_cpp::State::Id& t_id) {
    return t_os << t_id.name();
}