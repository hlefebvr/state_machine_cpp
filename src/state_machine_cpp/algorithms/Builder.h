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
};

class Algorithm::Builder::Indirection {
    const unsigned int m_level;
protected:
    State::Instance as_instance(const State::Any& t_state) const;
public:
    explicit Indirection(unsigned int t_level);
    unsigned int level() const;
};

class Algorithm::Builder::States : public Indirection {
public:
    explicit States(unsigned int t_level);

    virtual void create(const State::Any& t_state) = 0;
    virtual void remove(const State::Any& t_state) = 0;
};

class Algorithm::Builder::Transitions : public Indirection {
    virtual void create_or_override(bool t_do_override, const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler* t_handler) = 0;
    virtual void create_or_override_if(bool t_do_override, const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler* t_handler) = 0;
public:
    explicit Transitions(unsigned int t_level);

    // Trivial transitions
    void create(const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler& t_handler);
    void create(const State::Any& t_initial_state, const State::Any& t_next_state);
    void create_virtual(const State::Any& t_initial_state, const State::Any& t_next_state);
    void override(const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler& t_handler);
    void override(const State::Any& t_initial_state, const State::Any& t_next_state);

    // Conditional transitions
    void create_if(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler& t_handler);
    void create_if_virtual(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else);
    void override_if(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler& t_handler);

    // All
    virtual void remove(const State::Any& t_state) = 0;
};

#endif //STATE_MACHINE_CPP_BUILDER_H
