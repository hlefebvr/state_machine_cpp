//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_ALGORITHMTRANSITIONSPLOTTER_H
#define STATE_MACHINE_CPP_LIB_ALGORITHMTRANSITIONSPLOTTER_H

#include "AlgorithmBuilder.h"
#include <robin_hood/robin_hood.h>
#include <list>

namespace Algorithm {
    namespace Impl {
        namespace Explorer {
            class Transitions;
        }
    }
}

class Algorithm::Impl::Explorer::Transitions : public Algorithm::Builder::Transitions{
public:
    Transitions(robin_hood::unordered_map<std::string, std::list<std::string>>& t_transitions, unsigned int t_level);

    void remove(const State::Any &t_state) override;

private:
    robin_hood::unordered_map<std::string, std::list<std::string>>& m_transitions;

    void create_any_transition(const State::Instance& t_initial_instance,
                               std::list<std::string>&& t_list,
                               bool t_should_already_exist);

    void create_or_override(bool t_do_override,
                            const State::Any &t_initial_state,
                            const State::Any &t_next_state,
                            Transition::TrivialHandler & t_handler) override;

    void create_or_override_if(bool t_do_override,
                               const State::Any &t_initial_state,
                               const State::Any &t_if_true,
                               const State::Any &t_else,
                               Transition::ConditionalHandler & t_handler) override;

    bool has(const State::Instance& t_instance) const;
};


#endif //STATE_MACHINE_CPP_LIB_ALGORITHMTRANSITIONSPLOTTER_H
