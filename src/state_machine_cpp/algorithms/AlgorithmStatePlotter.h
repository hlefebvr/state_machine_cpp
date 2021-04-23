//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_LIB_ALGORITHMSTATEPLOTTER_H
#define STATE_MACHINE_CPP_LIB_ALGORITHMSTATEPLOTTER_H

#include "AlgorithmBuilder.h"
#include <robin_hood/robin_hood.h>
#include <list>

namespace Algorithm {
    namespace Impl {
        namespace Explorer {
            class States;
        }
    }
}

class Algorithm::Impl::Explorer::States : public Algorithm::Builder::States {
    robin_hood::unordered_map<std::string, std::list<std::string>>& m_transitions;
public:
    explicit States(robin_hood::unordered_map<std::string, std::list<std::string>>& t_transitions, unsigned int t_level);

    void create(const State::Any& t_state) override;
    void remove(const State::Any& t_state) override;

};


#endif //STATE_MACHINE_CPP_LIB_ALGORITHMSTATEPLOTTER_H
