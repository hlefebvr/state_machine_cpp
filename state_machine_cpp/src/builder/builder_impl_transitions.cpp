//
// Created by henri on 27/04/21.
//

#include <mutex>
#include <thread>
#include <list>
#include "builder/builder_impl_transitions.h"
#include "algorithms/algorithm.h"

state_machine_cpp::Algorithm::Impl::Build::Transitions::Transitions(state_machine_cpp::Algorithm::Instance &t_destination,
                                                                    const state_machine_cpp::Algorithm::Builder::Layers* t_layer)
        : Algorithm::Builder::Transitions(t_layer), m_destination(t_destination) {

}


void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_or_override(bool t_do_override,
                                                                                const State::Any &t_initial_state,
                                                                                const State::Any &t_next_state,
                                                                                Transition::TrivialHandler *t_handler) {
    m_destination.create_transition(
            as_instance(t_initial_state),
            as_instance(t_next_state),
            t_handler,
            t_do_override);
}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_or_override_if(bool t_do_override,
                                                                                   const State::Any &t_initial_state,
                                                                                   const State::Any &t_if_true,
                                                                                   const State::Any &t_else,
                                                                                   Transition::ConditionalHandler *t_handler) {

    m_destination.create_transition_if(
            as_instance(t_initial_state),
            as_instance(t_if_true),
            as_instance(t_else),
            t_handler,
            t_do_override);

}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::remove(const State::Any &t_state) {
    m_destination.remove_transition(as_instance(t_state));
}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::declare_as_final(const State::Any &t_state) {
    m_destination.set_as_final(as_instance(t_state));
}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_parallelized(
        const state_machine_cpp::State::Any &t_initial_state, std::initializer_list<State::Any> t_next_states,
        const state_machine_cpp::State::Any &t_final_state) {

    // Create next states (instantiate)
    std::vector<State::Instance> next_states;
    next_states.reserve(t_next_states.size() + 1);
    next_states.emplace_back(as_instance(t_final_state));
    for (const auto& any_state : t_next_states) {
        next_states.emplace_back(as_instance(any_state));
    }

    auto *destination = &m_destination;

    // Create handler
    auto handler = [t_final_state, next_states, destination](Context& t_context) -> int {

        std::list<std::thread> threads;

        auto final_state = next_states.front();

        for (const auto& initial_state : next_states) {
            threads.emplace_back([initial_state, final_state, &t_context, destination](){
                auto current_state = initial_state;
                while (current_state != final_state) {
                    current_state = destination->transitions()[current_state](t_context);
                }
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        return 0;
    };

    m_destination.create_any_transition(as_instance(t_initial_state),
                                        Transition::Type::Parallelized,
                                        std::move(next_states),
                                        handler,
                                        false
                                    );

}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::override_parallelized(
        const state_machine_cpp::State::Any &t_initial_state, std::initializer_list<State::Any> t_next_states,
        const state_machine_cpp::State::Any &t_final_state) {

    // Create next states (instantiate)
    std::vector<State::Instance> next_states;
    next_states.reserve(t_next_states.size() + 1);
    next_states.emplace_back(as_instance(t_final_state));
    for (const auto& any_state : t_next_states) {
        next_states.emplace_back(as_instance(any_state));
    }

    auto *destination = &m_destination;

    // Create handler
    auto handler = [t_final_state, next_states, destination](Context& t_context) -> int {

        std::list<std::thread> threads;

        auto final_state = next_states.front();

        for (const auto& initial_state : next_states) {
            threads.emplace_back([initial_state, final_state, &t_context, destination](){
                auto current_state = initial_state;
                while (current_state != final_state) {
                    current_state = destination->transitions()[current_state](t_context);
                }
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        return 0;
    };

    m_destination.create_any_transition(as_instance(t_initial_state),
                                        Transition::Type::Parallelized,
                                        std::move(next_states),
                                        handler,
                                        true
    );

}
