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
    Algorithm::Instance& m_destination;
    const Layers* m_layers;
    Algorithm::Mode m_build_mode;
protected:
    [[nodiscard]] State::Instance as_instance(const State::Any& t_state) const;
    [[nodiscard]] std::vector<State::Instance> as_instance(const std::list<State::Any>& t_states) const;

    [[nodiscard]] inline Algorithm::Mode build_mode() const;
    [[nodiscard]] inline const Algorithm::Instance& destination() const;
    inline Algorithm::Instance& destination();
public:
    explicit Indirection(Algorithm::Instance& t_destination, const Layers* t_layer, Algorithm::Mode t_build_mode);
};

state_machine_cpp::Algorithm::Mode state_machine_cpp::Algorithm::Builder::Indirection::build_mode() const {
    return m_build_mode;
}

state_machine_cpp::Algorithm::Instance &state_machine_cpp::Algorithm::Builder::Indirection::destination() {
    return m_destination;
}

const state_machine_cpp::Algorithm::Instance &state_machine_cpp::Algorithm::Builder::Indirection::destination() const {
    return m_destination;
}


#endif //STATE_MACHINE_CPP_BUILDER_INDIRECTION_H
