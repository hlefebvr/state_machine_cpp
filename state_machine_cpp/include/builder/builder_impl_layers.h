//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_IMPL_LAYERS_H
#define STATE_MACHINE_CPP_BUILDER_IMPL_LAYERS_H

#include <stack>
#include "builder_layers.h"

namespace state_machine_cpp::Algorithm::Impl::Build {
    class Layers;
}

class state_machine_cpp::Algorithm::Impl::Build::Layers : public Algorithm::Builder::Layers {
    std::stack<unsigned int> m_layers;
    unsigned int m_max_layer = 0;
public:
    [[nodiscard]] unsigned int current() const override;
    unsigned int create() override;
    unsigned int use(unsigned int t_layer) override;
    void close() override;
};


#endif //STATE_MACHINE_CPP_BUILDER_IMPL_LAYERS_H
