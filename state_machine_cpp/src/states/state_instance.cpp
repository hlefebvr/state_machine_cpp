//
// Created by henri on 27/04/21.
//

#include "states/state_instance.h"
#include "states/state_id.h"

std::ostream& operator<<(std::ostream& t_os, const state_machine_cpp::State::Instance& t_id) {
    return t_os << t_id.name();
}

state_machine_cpp::State::Instance::Instance(const State::Id &t_id) : m_id {&t_id} {
    update_hash();
}

state_machine_cpp::State::Instance::Instance(const State::Id &t_id, unsigned int t_layer) : m_id{&t_id}, m_layer{t_layer} {
    update_hash();
}

state_machine_cpp::State::Instance &state_machine_cpp::State::Instance::operator=(const State::Id &t_rhs)  {
    m_id = &t_rhs;
    m_layer = 0;
    update_hash();
    return *this;
}

void state_machine_cpp::State::Instance::update_hash() {
    m_hash = std::hash<std::string>()(name());
}

bool state_machine_cpp::State::Instance::equals_to(const State::Instance &t_rhs) const {
    return m_hash == t_rhs.m_hash;
}

std::string state_machine_cpp::State::Instance::name() const {
    if (!m_id) {
        return "UNDEFINED_STATE";
    }
    return m_id->m_name + '[' + std::to_string(m_layer) + ']';
}
