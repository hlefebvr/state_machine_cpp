//
// Created by henri on 22/04/21.
//

#include "AlgorithmStatePlotter.h"

Algorithm::Impl::Plot::States::States(unsigned int t_level) : Algorithm::Builder::States(t_level) {

}

void Algorithm::Impl::Plot::States::create(const State::Any &t_state) {
    std::cout << t_state.as_instance(level()) << ";" << std::endl;
}

void Algorithm::Impl::Plot::States::remove(const State::Any &t_state) {
    // TODO
}
