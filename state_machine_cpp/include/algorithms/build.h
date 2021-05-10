//
// Created by henri on 26/04/21.
//

#ifndef STATE_MACHINE_CPP_BUILD_H
#define STATE_MACHINE_CPP_BUILD_H

#include "builder/builder_impl_states.h"
#include "builder/builder_impl_transitions.h"
#include "builder/builder_impl_layers.h"
#include "builder/builder_types.h"

namespace state_machine_cpp::Algorithm {
    namespace Impl {
        template<typename T> struct has_INITIAL_STATE;
        template<typename T> struct has_FINAL_STATE;
        template<typename T> struct has_TIME_LIMIT_REACHED_STATE;
    }
    class Instance;
}


template <typename T>
struct state_machine_cpp::Algorithm::Impl::has_INITIAL_STATE {
    template <class, class> class checker;
    template <typename C> static std::true_type test(checker<C, decltype(&C::INITIAL_STATE)> *) { return {}; }
    template <typename C> static std::false_type test(...) { return {}; }
    typedef decltype(test<T>(nullptr)) type;
    static constexpr bool value = std::is_same<std::true_type, decltype(test<T>(nullptr))>::value;
};

template <typename T>
struct state_machine_cpp::Algorithm::Impl::has_FINAL_STATE {
    template <class, class> class checker;
    template <typename C> static std::true_type test(checker<C, decltype(&C::FINAL_STATE)> *) { return {}; }
    template <typename C> static std::false_type test(...) { return {}; }
    typedef decltype(test<T>(nullptr)) type;
    static constexpr bool value = std::is_same<std::true_type, decltype(test<T>(nullptr))>::value;
};

template <typename T>
struct state_machine_cpp::Algorithm::Impl::has_TIME_LIMIT_REACHED_STATE {
    template <class, class> class checker;
    template <typename C> static std::true_type test(checker<C, decltype(&C::TIME_LIMIT_REACHED)> *) { return {}; }
    template <typename C> static std::false_type test(...) { return {}; }
    typedef decltype(test<T>(nullptr)) type;
    static constexpr bool value = std::is_same<std::true_type, decltype(test<T>(nullptr))>::value;
};

template<class T>
void state_machine_cpp::Algorithm::build(Algorithm::Instance& t_destination, Algorithm::Mode t_build_mode) {

    Impl::Build::Layers layers;
    Impl::Build::States states(t_destination, &layers, t_build_mode);
    Impl::Build::Transitions transitions(t_destination, &layers, t_build_mode);

    Algorithm::Builder::inherit<T>(states, transitions, layers);

    if (layers.current() != 0) {
        throw std::runtime_error("There were some opened layers which failed to be closed.");
    }

    if constexpr(Impl::has_INITIAL_STATE<T>::value) {
        if (!t_destination.transitions().has(T::INITIAL_STATE)) {
            throw std::runtime_error("INITIAL_STATE have been auto-detected yet the state is not created within the algorithm."
                                     "Call states.create.");
        }
        t_destination.set_initial_state(T::INITIAL_STATE);
    }

    if constexpr(Impl::has_FINAL_STATE<T>::value) {
        if (!t_destination.transitions().has(T::FINAL_STATE)) {
            throw std::runtime_error("FINAL_STATE have been auto-detected yet the state is not created within the algorithm."
                                     "Call states.create.");
        }
        t_destination.set_final_state(T::FINAL_STATE);
    }

    if constexpr(Impl::has_TIME_LIMIT_REACHED_STATE<T>::value) {
        if (!t_destination.transitions().has(T::TIME_LIMIT_REACHED)) {
            throw std::runtime_error("TIME_LIMIT_REACHED have been auto-detected yet the state is not created within the algorithm."
                                     "Call states.create.");
        }
        t_destination.set_time_limit_reached_state(T::TIME_LIMIT_REACHED);
    }

}

#endif //STATE_MACHINE_CPP_BUILD_H
