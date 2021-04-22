//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_H
#define STATE_MACHINE_CPP_BUILDER_H

#include <iostream>
#include "../states/StateAny.h"
#include "../transitions/TransitionHandler.h"

namespace Algorithm {
    class Builder;
    class Instance;
}

class Algorithm::Builder {
public:
    class States;
    class Transitions;

    virtual void build(States& states, Transitions& transitions) = 0;
private:
    class Indirection;
    static State::Instance as_instance(const State::Any& t_state, unsigned int t_level_if_not_set);
};

class Algorithm::Builder::Indirection {
    Algorithm::Instance& m_destination;
    const unsigned int m_level;
public:
    Indirection(Algorithm::Instance& t_destination, unsigned int t_level);
    Algorithm::Instance& destination();
    unsigned int level() const;
};

class Algorithm::Builder::States : public Indirection {
public:
    States(Algorithm::Instance& t_destination, unsigned int t_level);

    void create(const State::Any& t_state);
    void remove(const State::Any& t_state);
};

class Algorithm::Builder::Transitions : public Indirection {
    void create_or_override(bool t_do_override, const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler& t_handler);
    void create_or_override_if(bool t_do_override, const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler& t_handler);
public:
    Transitions(Algorithm::Instance& t_destination, unsigned int t_level);

    // Trivial transitions
    void create(const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler& t_handler);
    void override(const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler& t_handler);

    // Conditional transitions
    void create_if(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler& t_handler);
    void override_if(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler& t_handler);

    // All
    void remove(const State::Any& t_state);
};

#endif //STATE_MACHINE_CPP_BUILDER_H
