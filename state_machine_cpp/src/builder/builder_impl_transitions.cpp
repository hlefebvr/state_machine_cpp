//
// Created by henri on 27/04/21.
//

#include <mutex>
#include <thread>
#include <list>
#include "builder/builder_impl_transitions.h"
#include "algorithms/algorithm.h"

state_machine_cpp::Algorithm::Impl::Build::Transitions::Transitions(state_machine_cpp::Algorithm::Instance &t_destination,
                                                                    const state_machine_cpp::Algorithm::Builder::Layers* t_layer,
                                                                    Algorithm::Mode t_build_mode)
        : Algorithm::Builder::Transitions(t_destination, t_layer, t_build_mode) {

}

// HANDLER CREATORS

std::function<int(state_machine_cpp::Context2 & )> state_machine_cpp::Algorithm::Impl::Build::Transitions::wrap_with_logs(
        const state_machine_cpp::State::Instance &t_initial_state,
        std::function<int(Context2 &)> &&t_function) {

    return [t_function, t_initial_state](Context2& t_context){
        std::cout << "-- state: " << t_initial_state << std::endl;
        return t_function(t_context);
    };

}

std::function<int(state_machine_cpp::Context2 & )>
state_machine_cpp::Algorithm::Impl::Build::Transitions::create_direct_handler(
        const State::Instance &t_initial_state,
        state_machine_cpp::Transition::TrivialHandler *t_handler) {

    if (!t_handler) {
        return {};
    }

    auto result = [t_handler](Context2& t_context){
        (*t_handler)(t_context);
        return 0;
    };

    if (build_mode() == Mode::Debug) {
        return wrap_with_logs(t_initial_state, std::move(result));
    }

    return result;
}

std::function<int(state_machine_cpp::Context2 & )> state_machine_cpp::Algorithm::Impl::Build::Transitions::create_conditional_handler(
        const State::Instance &t_initial_state,
        state_machine_cpp::Transition::ConditionalHandler *t_handler) {

    if (!t_handler) {
        return {};
    }

    auto result = [t_handler](Context2& t_context) {
        return (*t_handler)(t_context);
    };

    if (build_mode() == Mode::Debug) {
        return wrap_with_logs(t_initial_state, std::move(result));
    }

    return result;
}

std::function<int(state_machine_cpp::Context2 & )>
state_machine_cpp::Algorithm::Impl::Build::Transitions::create_parallelized_handler(
        const state_machine_cpp::State::Instance &t_initial_state,
        const std::vector<state_machine_cpp::State::Instance>& t_next_states,
        const state_machine_cpp::State::Any &t_final_state) {

    auto *ptr_destination = &destination();

    // Create handler
    auto result = [t_final_state, t_next_states, ptr_destination](Context2& t_context) -> int {

        std::list<std::thread> threads;

        auto final_state = t_next_states.back();

        for (const auto& initial_state : t_next_states) {
            threads.emplace_back([initial_state, final_state, &t_context, ptr_destination](){
                auto current_state = initial_state;
                while (current_state != final_state) {
                    current_state = ptr_destination->transitions()[current_state](t_context);
                }
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        return (int) t_next_states.size() - 1;
    };

    return result;
}

// TRANSITION CREATORS

void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_or_override(bool t_is_override,
                                                                                const State::Any &t_initial_state,
                                                                                const State::Any &t_next_state,
                                                                                Transition::TrivialHandler *t_handler) {

    auto initial_state = as_instance(t_initial_state);
    auto handler = create_direct_handler(initial_state, t_handler);
    std::vector<State::Instance> next_instance = { as_instance(t_next_state) };

    destination().create_any_transition(
            initial_state,
            Transition::Type::Direct,
            std::move(next_instance),
            std::move(handler),
            t_is_override);

}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_or_override_if(bool t_is_override,
                                                                                   const State::Any &t_initial_state,
                                                                                   const State::Any &t_if_true,
                                                                                   const State::Any &t_else,
                                                                                   Transition::ConditionalHandler *t_handler) {

    auto initial_state = as_instance(t_initial_state);
    auto handler = create_conditional_handler(initial_state, t_handler);
    std::vector<State::Instance> next_states = {as_instance(t_else), as_instance(t_if_true) };

    destination().create_any_transition(
            initial_state,
            Transition::Type::Conditional,
            std::move(next_states),
            std::move(handler),
            t_is_override);

}

void state_machine_cpp::Algorithm::Impl::Build::Transitions::create_or_override_parallelized(bool t_is_override,
                                                                                             const state_machine_cpp::State::Any &t_initial_state,
                                                                                             std::initializer_list<State::Any> t_next_states,
                                                                                             const state_machine_cpp::State::Any &t_final_state) {

    auto initial_state = as_instance(t_initial_state);
    auto next_states = as_instance(t_next_states);
    next_states.emplace_back(as_instance(t_final_state));
    auto handler = create_parallelized_handler(initial_state, next_states, t_final_state);

    destination().create_any_transition(initial_state,
                                        Transition::Type::Parallelized,
                                        std::move(next_states),
                                        std::move(handler),
                                        t_is_override
    );

}

// TRANSITION REMOVE

void state_machine_cpp::Algorithm::Impl::Build::Transitions::remove(const State::Any &t_state) {
    destination().remove_transition(as_instance(t_state));
}

// FINAL TRANSITION

void state_machine_cpp::Algorithm::Impl::Build::Transitions::declare_as_final(const State::Any &t_state) {
    destination().set_as_final(as_instance(t_state));
}
