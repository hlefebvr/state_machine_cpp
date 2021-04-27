//
// Created by henri on 21/04/21.
//

#include "states.h"

#include <iostream>

State::Id::Id(const char *t_name) noexcept : m_name(t_name), m_hash(std::hash<std::string>()(t_name)) {}

std::ostream& operator<<(std::ostream& t_os, const State::Id& t_id) {
    return t_os << t_id.name();
}

std::ostream& operator<<(std::ostream& t_os, const State::Instance& t_id) {
    return t_os << t_id.name();
}

State::Instance::Instance(const State::Id &t_id) : m_id {&t_id} {
    update_hash();
}

State::Instance::Instance(const State::Id &t_id, unsigned int t_layer) : m_id{&t_id}, m_layer{t_layer} {
    update_hash();
}

State::Instance &State::Instance::operator=(const State::Id &t_rhs)  {
    m_id = &t_rhs;
    m_layer = 0;
    update_hash();
    return *this;
}

void State::Instance::update_hash() {
    m_hash = std::hash<std::string>()(name());
}

bool State::Instance::equals_to(const State::Instance &t_rhs) const {
    return m_hash == t_rhs.m_hash;
}

std::string State::Instance::name() const {
    if (!m_id) {
        return "UNDEFINED_STATE";
    }
    return m_id->m_name + '[' + std::to_string(m_layer) + ']';
}
