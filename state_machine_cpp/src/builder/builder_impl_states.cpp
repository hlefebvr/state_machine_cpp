//
// Created by henri on 27/04/21.
//

#include "builder/builder_impl_states.h"
#include "algorithms/algorithm.h"

state_machine_cpp::Algorithm::Impl::Build::States::States(state_machine_cpp::Algorithm::Instance &t_destination,
                                                          const state_machine_cpp::Algorithm::Builder::Layers* t_layer,
                                                          Algorithm::Mode t_build_mode)
        : state_machine_cpp::Algorithm::Builder::States(t_destination, t_layer, t_build_mode) {

}

void state_machine_cpp::Algorithm::Impl::Build::States::create(const state_machine_cpp::State::Any &t_state) {
    destination().create_state(as_instance(t_state));
}

void state_machine_cpp::Algorithm::Impl::Build::States::remove(const state_machine_cpp::State::Any &t_state) {
    destination().remove_state(as_instance(t_state));
}
