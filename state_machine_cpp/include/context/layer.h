//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_LAYER_H
#define STATE_MACHINE_CPP_LAYER_H

#include "abstract_layer.h"
#include <memory>

namespace state_machine_cpp {
    template<class ...> class Layer;
}

template<class ...Attributes>
class state_machine_cpp::Layer : public state_machine_cpp::AbstractLayer, public std::shared_ptr<Attributes>... {
public:
    Layer() = default;
    Layer(Attributes* ...t_ptr) : std::shared_ptr<Attributes>(t_ptr)... {}
};

template<>
class state_machine_cpp::Layer<> : public state_machine_cpp::AbstractLayer {
public:
    Layer() = default;
    Layer(void*) {}
};


#endif //STATE_MACHINE_CPP_LAYER_H
