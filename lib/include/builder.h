//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_H
#define STATE_MACHINE_CPP_BUILDER_H

#include <iostream>
#include "states.h"
#include "transitions.h"

namespace state_machine_cpp {
    namespace Algorithm {
        class Builder;
        class Instance;
        template<class T> void build(Algorithm::Instance& t_destination);
    }
}

class state_machine_cpp::Algorithm::Builder {
public:
    class States;
    class Transitions;
    class Layers;

    template<class T> friend void ::state_machine_cpp::Algorithm::build(Algorithm::Instance& t_destination);

    virtual void build(States& states, Transitions& transitions, Layers& layers) = 0;
protected:
    template<class T> static void inherit(States& states, Transitions& transitions, Layers& layers);
private:
    class Indirection;
};

class state_machine_cpp::Algorithm::Builder::Layers {
public:
    virtual unsigned int current() const = 0;
    virtual unsigned int create() = 0;
    virtual unsigned int use(unsigned int t_layer) = 0;
    virtual void close() = 0;
};

class state_machine_cpp::Algorithm::Builder::Indirection {
    const Layers* m_layers;
protected:
    State::Instance as_instance(const State::Any& t_state) const;
public:
    explicit Indirection(const Layers* t_layer);
};

class state_machine_cpp::Algorithm::Builder::States : public Indirection {
public:
    explicit States(const Layers* t_layer);

    virtual void create(const State::Any& t_state) = 0;
    virtual void remove(const State::Any& t_state) = 0;
};

class state_machine_cpp::Algorithm::Builder::Transitions : public Indirection {
    virtual void create_or_override(bool t_do_override, const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler* t_handler) = 0;
    virtual void create_or_override_if(bool t_do_override, const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler* t_handler) = 0;
public:
    explicit Transitions(const Layers* t_layer);

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
    virtual void declare_as_final(const State::Any& t_state) = 0;
};

template<class T>
void state_machine_cpp::Algorithm::Builder::inherit(Algorithm::Builder::States &states, Algorithm::Builder::Transitions &transitions, Layers& layers) {
    T builder;
    builder.build(states, transitions, layers);
}

#endif //STATE_MACHINE_CPP_BUILDER_H
