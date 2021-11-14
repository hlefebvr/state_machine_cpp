//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILDER_TRANSITIONS_H
#define STATE_MACHINE_CPP_BUILDER_TRANSITIONS_H

#include "builder_indirection.h"
#include "transitions/transition_handlers.h"

class state_machine_cpp::Algorithm::Builder::Transitions : public Indirection {
protected:
    virtual void create_or_override(bool t_is_override, const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler* t_handler, std::string&& t_description) = 0;
    virtual void create_or_override_if(bool t_is_override, const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler* t_handler, std::string&& t_description) = 0;
    virtual void create_or_override_parallelized(bool t_is_override, const State::Any &t_initial_state, std::initializer_list<State::Any> t_next_states, const State::Any &t_final_state, std::string&& t_description) = 0;
public:
    explicit Transitions(Algorithm::Instance& t_destination, const Layers* t_layer, Algorithm::Mode t_build_mode);

    // Trivial transitions
    void create(const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler& t_handler, std::string t_description = "");
    void create(const State::Any& t_initial_state, const State::Any& t_next_state, std::string t_description = "");
    void create_virtual(const State::Any& t_initial_state, const State::Any& t_next_state, std::string t_description = "");
    void override(const State::Any& t_initial_state, const State::Any& t_next_state, Transition::TrivialHandler& t_handler, std::string t_description = "");
    void override(const State::Any& t_initial_state, const State::Any& t_next_state, std::string t_description = "");

    // Conditional transitions
    void create_if(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler& t_handler, std::string t_description = "");
    void create_if_virtual(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, std::string t_description = "");
    void override_if(const State::Any& t_initial_state, const State::Any& t_if_true, const State::Any& t_else, Transition::ConditionalHandler& t_handler, std::string t_description = "");

    // Parallel transitions
    void create_parallelized(const State::Any& t_initial_state, std::initializer_list<State::Any> t_next_states, const State::Any& t_final_state, std::string t_description = "");
    void override_parallelized(const State::Any& t_initial_state, std::initializer_list<State::Any> t_next_states, const State::Any& t_final_state, std::string t_description = "");

    // All
    virtual void remove(const State::Any& t_state) = 0;
    virtual void declare_as_final(const State::Any& t_state) = 0;
};


#endif //STATE_MACHINE_CPP_BUILDER_TRANSITIONS_H
