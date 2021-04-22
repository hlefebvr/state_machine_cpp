//
// Created by henri on 22/04/21.
//

#include "AlgorithmTransitionsPlotter.h"

Algorithm::Impl::Plot::Transitions::Transitions(unsigned int t_level)
    : Algorithm::Builder::Transitions(t_level) {

}

void Algorithm::Impl::Plot::Transitions::remove(const State::Any &t_state) {
    // TODO
}

void Algorithm::Impl::Plot::Transitions::create_or_override(bool t_do_override,
                                                            const State::Any &t_initial_state,
                                                            const State::Any &t_next_state,
                                                            Transition::TrivialHandler &t_handler) {
    // TODO
    std::cout << t_initial_state.as_instance(level()) << " -- " << t_next_state.as_instance(level()) << ";" << std::endl;
}

void Algorithm::Impl::Plot::Transitions::create_or_override_if(bool t_do_override,
                                                               const State::Any &t_initial_state,
                                                               const State::Any &t_if_true,
                                                               const State::Any &t_else,
                                                               Transition::ConditionalHandler &t_handler) {
    // TODO
    std::cout << t_initial_state.as_instance(level()) << " -- " << t_if_true.as_instance(level()) << ";" << std::endl;
    std::cout << t_initial_state.as_instance(level()) << " -- " << t_else.as_instance(level()) << ";" << std::endl;
}
