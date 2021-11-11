//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_H
#define STATE_MACHINE_CPP_CONTEXT_H

#include <limits>
#include <memory>
#include "impl/__timer.h"
#include "impl/__pointer.h"
#include "states/state_instance.h"
#include "states/state_any.h"
#include "abstract_layer.h"
#include "merge.h"

namespace state_machine_cpp {
    class Context;
    namespace Algorithm {
        class Instance;
        void run(const Algorithm::Instance& t_instance, Context& t_context);
    }
}

class state_machine_cpp::Context {
    std::shared_ptr<AbstractAttributeTree> m_underlying_context;

    State::Instance m_state;
    double m_time_limit_in_seconds = std::numeric_limits<double>::max();
    Timer m_timer;

    friend void ::state_machine_cpp::Algorithm::run(const Algorithm::Instance& t_instance, Context& t_context);
    void set_state(const State::Any& t_state) { m_state = t_state.as_instance(0); }

    void start_timer() { m_timer.start(); }
    void stop_timer() { m_timer.stop(); }
public:

    explicit Context(AbstractAttributeTree* t_underlying_context) : m_underlying_context(t_underlying_context) {}

    [[nodiscard]] unsigned int layer() const { return m_state.layer(); }
    [[nodiscard]] const State::Instance& state() const { return m_state; }
    [[nodiscard]] double execution_time_in_seconds() const { return m_timer.time_in_seconds(); }
    [[nodiscard]] double remaining_time_in_seconds() const { return m_time_limit_in_seconds - m_timer.time_in_seconds(); }
    [[nodiscard]] bool has_reached_time_limit() const { return remaining_time_in_seconds() <= 0; }
    void set_time_limit_in_seconds(double t_time_limit) { m_time_limit_in_seconds = t_time_limit; }

    template<class T> T& get(int t_layer = -1) {
        const unsigned int index = t_layer == -1 ? layer() : t_layer;
        auto& layer = m_underlying_context->layer(index);
        return *dynamic_cast<std::shared_ptr<T>&>(layer).get();
    }

    template<class T> const T& get(int t_layer = -1) const {
        return const_cast<Context&>(*this).get<T>(t_layer);
    }

    template<class ...X, class ...Y>
    static merge_t<AttributeTree<X...>, AttributeTree<Y...>>* join(AttributeTree<X...>&& t_x, AttributeTree<Y...>&& t_y) {
        auto* result = new merge_t<AttributeTree<X...>, AttributeTree<Y...>>();
        Impl::merge<std::tuple<X...>, AttributeTree<X...>>::to(&t_x, *result);
        Impl::merge<std::tuple<Y...>, AttributeTree<Y...>>::to(&t_y, *result);
        return result;
    }

    template<class T> T& get_relative(int t_offset) { return get<T>(layer() + t_offset); }
    template<class T> const T& get_relative(int t_offset) const { return get<T>(layer() + t_offset); }

    template<class T, class ...X> static Context create(X... t_args) {
        return Context(T::create_attributes(t_args...));
    }

};

#endif //STATE_MACHINE_CPP_CONTEXT_H
