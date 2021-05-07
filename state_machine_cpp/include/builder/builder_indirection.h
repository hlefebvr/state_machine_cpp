//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_INDIRECTION_H
#define STATE_MACHINE_CPP_BUILDER_INDIRECTION_H

#include <list>
#include <vector>
#include "builder.h"
#include "states/state_any.h"

class state_machine_cpp::Algorithm::Builder::Indirection {
    const Layers* m_layers;
protected:
    [[nodiscard]] State::Instance as_instance(const State::Any& t_state) const;
    [[nodiscard]] std::vector<State::Instance> as_instance(const std::list<State::Any>& t_states) const;
public:
    explicit Indirection(const Layers* t_layer);
};

#endif //STATE_MACHINE_CPP_BUILDER_INDIRECTION_H
