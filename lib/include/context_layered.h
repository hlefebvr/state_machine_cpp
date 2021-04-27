//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_LAYERED_H
#define STATE_MACHINE_CPP_CONTEXT_LAYERED_H

#include <array>
#include "context.h"

namespace state_machine_cpp {
    template<unsigned int N_LAYER> class LayeredContext;
}

template<unsigned int N_LAYER>
class state_machine_cpp::LayeredContext : public Context {
    std::array<Context*, N_LAYER> m_layers;
protected:
    Context *operator[](unsigned int t_index) override {
        return m_layers[t_index];
    }
    const Context *operator[](unsigned int t_index) const override {
        return m_layers[t_index];
    }
public:
    LayeredContext() = default;
    template<class ...Args> explicit LayeredContext(Args& ...t_args) : Context(), m_layers({&t_args...}) {}
    void set(unsigned int t_layer, Context& t_value) { m_layers[t_layer] = &t_value; }
};

#endif //STATE_MACHINE_CPP_CONTEXT_LAYERED_H
