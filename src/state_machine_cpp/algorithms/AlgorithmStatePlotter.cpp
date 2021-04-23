//
// Created by henri on 22/04/21.
//

#include "AlgorithmStatePlotter.h"

Algorithm::Impl::Explorer::States::States(robin_hood::unordered_map<std::string, std::list<std::string>>& t_transitions,
                                      unsigned int t_level)
  : Algorithm::Builder::States(t_level), m_transitions(t_transitions) {

}

void Algorithm::Impl::Explorer::States::create(const State::Any &t_state) {

    auto instance = as_instance(t_state);
    auto it = m_transitions.find(instance.name());
    if (it != m_transitions.end()) {
        throw std::runtime_error("Cannot create twice the same state instance.");
    }
    m_transitions.emplace(as_instance(t_state).name(), std::list<std::string>());

}

void Algorithm::Impl::Explorer::States::remove(const State::Any &t_state) {

    auto instance = as_instance(t_state);
    auto it = m_transitions.find(instance.name());
    if (it == m_transitions.end()) {
        throw std::runtime_error("Cannot remove a non-existing state instance");
    }
    m_transitions.erase(it);

}
