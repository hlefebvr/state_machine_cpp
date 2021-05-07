//
// Created by henri on 27/04/21.
//

#include "builder/builder_indirection.h"
#include "builder/builder_layers.h"

state_machine_cpp::Algorithm::Builder::Indirection::Indirection(Algorithm::Instance& t_destination,
                                                                const Layers* t_layers,
                                                                Algorithm::Mode t_build_mode)
    : m_destination(t_destination),
      m_layers(t_layers),
      m_build_mode(t_build_mode) {

}

state_machine_cpp::State::Instance state_machine_cpp::Algorithm::Builder::Indirection::as_instance(const State::Any &t_any) const {
    return t_any.as_instance(m_layers->current());
}

std::vector<state_machine_cpp::State::Instance>
state_machine_cpp::Algorithm::Builder::Indirection::as_instance(const std::list<state_machine_cpp::State::Any> &t_states) const {

    std::vector<State::Instance> result;
    result.reserve(t_states.size());
    for (const auto& any_state : t_states) {
        result.emplace_back(as_instance(any_state));
    }

    return result;
}
