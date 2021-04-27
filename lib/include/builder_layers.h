//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_LAYERS_H
#define STATE_MACHINE_CPP_BUILDER_LAYERS_H

#include "builder.h"

class state_machine_cpp::Algorithm::Builder::Layers {
public:
    virtual unsigned int current() const = 0;
    virtual unsigned int create() = 0;
    virtual unsigned int use(unsigned int t_layer) = 0;
    virtual void close() = 0;
};


#endif //STATE_MACHINE_CPP_BUILDER_LAYERS_H
