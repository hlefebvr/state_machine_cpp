//
// Created by henri on 27/04/21.
//

#include "builder_impl_states.h"
#include "algorithm.h"

state_machine_cpp::Algorithm::Impl::Build::States::States(state_machine_cpp::Algorithm::Instance &t_destination,
                                                          const state_machine_cpp::Algorithm::Builder::Layers* t_layer)
        : state_machine_cpp::Algorithm::Builder::States(t_layer), m_destination(t_destination) {

}

void state_machine_cpp::Algorithm::Impl::Build::States::create(const state_machine_cpp::State::Any &t_state) {
    m_destination.create_state(as_instance(t_state));
}

void state_machine_cpp::Algorithm::Impl::Build::States::remove(const state_machine_cpp::State::Any &t_state) {
    m_destination.remove_state(as_instance(t_state));
}
