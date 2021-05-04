//
// Created by henri on 27/04/21.
//

#include <stdexcept>
#include "builder/builder_impl_layers.h"

unsigned int state_machine_cpp::Algorithm::Impl::Build::Layers::current() const {
    return m_layers.empty() ? 0 : m_layers.top();
}

unsigned int state_machine_cpp::Algorithm::Impl::Build::Layers::create() {
    ++m_max_layer;
    m_layers.emplace(m_max_layer);
    return current();
}

unsigned int state_machine_cpp::Algorithm::Impl::Build::Layers::use(unsigned int t_layer) {
    if (t_layer > m_max_layer) {
        throw std::runtime_error("The level you are trying to use has not been created. Use create first.");
    }
    m_layers.emplace(t_layer);
    return current();
}

void state_machine_cpp::Algorithm::Impl::Build::Layers::close() {
    if (m_layers.empty()) {
        throw std::runtime_error("Cannot close root layer");
    }
    m_layers.pop();
}

