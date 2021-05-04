//
// Created by henri on 04/05/21.
//

#include "context/context_auto.h"

state_machine_cpp::Context *state_machine_cpp::AutoContext::operator[](unsigned int t_index) {
    return Context::call_square_bracket_operator_on(m_context.get(), t_index);
}

const state_machine_cpp::Context *state_machine_cpp::AutoContext::operator[](unsigned int t_index) const {
    return Context::call_square_bracket_operator_on(m_context.get(), t_index);
}

state_machine_cpp::AutoContext::~AutoContext() {
    for (auto ptr : m_attributes) {
        delete ptr;
    }
}
