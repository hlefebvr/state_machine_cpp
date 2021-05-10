//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_H
#define STATE_MACHINE_CPP_CONTEXT_H

#include <functional>
#include "impl/__timer.h"
#include "impl/__pointer.h"
#include "states/state_instance.h"
#include "states/state_any.h"

namespace state_machine_cpp {
    class Context;
    namespace Algorithm {
        class Instance;
        void run(const Algorithm::Instance& t_instance, Context& t_context);
    }
}

class state_machine_cpp::Context {
    State::Instance m_state;
    double m_time_limit_in_seconds = std::numeric_limits<double>::max();
    Timer m_timer;

    friend void ::state_machine_cpp::Algorithm::run(const Algorithm::Instance& t_instance, Context& t_context);
    void set_state(const State::Any& t_state) { m_state = t_state.as_instance(0); }

    void start_timer() { m_timer.start(); }
    void stop_timer() { m_timer.stop(); }
protected:
    virtual Context* operator[](unsigned int t_index) = 0;
    virtual const Context* operator[](unsigned int t_index) const = 0;

    static Context* call_square_bracket_operator_on(Context* t_context, unsigned int t_index) { return t_context->operator[](t_index); }
    static const Context* call_square_bracket_operator_on(const Context* t_context, unsigned int t_index) { return t_context->operator[](t_index); }
public:
    virtual ~Context() = default;

    [[nodiscard]] unsigned int layer() const { return m_state.layer(); }
    [[nodiscard]] const State::Instance& state() const { return m_state; }
    [[nodiscard]] double execution_time_in_seconds() const { return m_timer.time_in_seconds(); }
    [[nodiscard]] double remaining_time_in_seconds() const { return m_time_limit_in_seconds - m_timer.time_in_seconds(); }
    [[nodiscard]] bool has_reached_time_limit() const { return remaining_time_in_seconds() <= 0; }
    void set_time_limit_in_seconds(double t_time_limit) { m_time_limit_in_seconds = t_time_limit; }

    template<class T> T& get(int t_index = -1) {
        const unsigned int index = t_index == -1 ? layer() : t_index;
        auto* ptr = dynamic_cast<Pointer<T>*>(this->operator[](index));
        if (ptr == nullptr) {
            throw std::runtime_error("Context could not be casted so as to return the desired type");
        }
        return **ptr;
    }

    template<class T> const T& get(int t_index = -1) const {
        const unsigned int index = t_index == -1 ? layer() : t_index;
        auto* ptr = dynamic_cast<const Pointer<T>*>(this->operator[](index));
        if (ptr == nullptr) {
            throw std::runtime_error("Context could not be casted so as to return the desired type");
        }
        return **ptr;
    }

    template<class T> T& get_relative(int t_offset) { return get<T>(layer() + t_offset); }
    template<class T> const T& get_relative(int t_offset) const { return get<T>(layer() + t_offset); }

};


#endif //STATE_MACHINE_CPP_CONTEXT_H
