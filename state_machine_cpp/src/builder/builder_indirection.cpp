//
// Created by henri on 27/04/21.
//

#include "builder/builder_indirection.h"
#include "builder/builder_layers.h"

state_machine_cpp::Algorithm::Builder::Indirection::Indirection(const Layers* t_layers) : m_layers(t_layers) {

}

state_machine_cpp::State::Instance state_machine_cpp::Algorithm::Builder::Indirection::as_instance(const State::Any &t_any) const {
    return t_any.as_instance(m_layers->current());
}
