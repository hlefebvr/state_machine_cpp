//
// Created by henri on 22/04/21.
//

#include "AlgorithmStateBuilder.h"
#include "AlgorithmInstance.h"

Algorithm::Impl::Build::States::States(Algorithm::Instance &t_destination, unsigned int t_level)
    : Algorithm::Builder::States(t_level), m_destination(t_destination) {

}

void Algorithm::Impl::Build::States::create(const State::Any &t_state) {
    m_destination.create_state(as_instance(t_state));
}

void Algorithm::Impl::Build::States::remove(const State::Any &t_state) {
    m_destination.remove_state(as_instance(t_state));
}
