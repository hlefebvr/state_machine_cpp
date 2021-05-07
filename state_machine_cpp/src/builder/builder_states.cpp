//
// Created by henri on 27/04/21.
//

#include "builder/builder_states.h"

state_machine_cpp::Algorithm::Builder::States::States(Algorithm::Instance& t_destination, const Layers* t_layer, Algorithm::Mode t_build_mode)
    : Indirection(t_destination, t_layer, t_build_mode) {

}
