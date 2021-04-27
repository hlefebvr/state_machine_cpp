//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_INDIRECTION_H
#define STATE_MACHINE_CPP_BUILDER_INDIRECTION_H

#include "builder.h"
#include "state_any.h"

class state_machine_cpp::Algorithm::Builder::Indirection {
    const Layers* m_layers;
protected:
    State::Instance as_instance(const State::Any& t_state) const;
public:
    explicit Indirection(const Layers* t_layer);
};

#endif //STATE_MACHINE_CPP_BUILDER_INDIRECTION_H
