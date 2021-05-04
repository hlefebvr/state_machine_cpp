//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_H
#define STATE_MACHINE_CPP_CONTEXT_H

#include "impl/__pointer.h"
#include "states/state_id.h"

namespace state_machine_cpp {
    class Context;
    namespace Algorithm {
        class Instance;
        namespace Impl {
            void run(::state_machine_cpp::Context &t_context,
                     const ::state_machine_cpp::State::Id &t_initial_state,
                     const ::state_machine_cpp::State::Id &t_final_state,
                     const std::function<State::Instance(const Algorithm::Instance &t_instance,
                                                         const State::Instance &t_state,
                                                         Context &t_context)> &t_apply_transition);
        }
    }
}

class state_machine_cpp::Context {
    State::Instance m_state;

    friend void ::state_machine_cpp::Algorithm::Impl::run(::state_machine_cpp::Context& t_context,
                                                     const ::state_machine_cpp::State::Id& t_initial_state,
                                                     const ::state_machine_cpp::State::Id& t_final_state,
                                                     const std::function<State::Instance(const State::Instance &t_state, Context &t_context)>& t_apply_transition);
    void set_state(State::Any t_state) { m_state = t_state.as_instance(0); }
protected:
    virtual Context* operator[](unsigned int t_index) = 0;
    virtual const Context* operator[](unsigned int t_index) const = 0;
public:
    virtual ~Context() = default;

    unsigned int layer() const { return m_state.layer(); }

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
