//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_TRANSITIONS_H
#define STATE_MACHINE_CPP_BUILDER_TRANSITIONS_H

#include "builder.h"
#include "builder_indirection.h"
#include "transition_handlers.h"

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


#endif //STATE_MACHINE_CPP_BUILDER_TRANSITIONS_H
