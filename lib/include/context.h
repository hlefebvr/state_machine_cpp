//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_H
#define STATE_MACHINE_CPP_CONTEXT_H

#include "__pointer.h"
#include "states.h"

namespace Algorithm {
    void run(const Algorithm::Instance& t_instance,
             Context& t_context,
             const State::Id& t_initial_state,
             const State::Id& t_final_state);
}

class Context {
    State::Instance m_state;

    friend void Algorithm::run(const Algorithm::Instance& t_instance,
                               Context& t_context,
                               const State::Id& t_initial_state,
                               const State::Id& t_final_state);
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

template<class ...Args>
struct SimpleContext : public Context, public Pointer<Args>... {

    SimpleContext() : Pointer<Args>()... {} // NOLINT(modernize-use-equals-default)
    explicit SimpleContext(Args& ...t_args) : Pointer<Args>(&t_args)... {}

    template<class T> void set(T& t_value) { Pointer<T>::operator=(&t_value); }
    using Context::get;
protected:
    Context *operator[](unsigned int t_index) override { return this; }
    const Context *operator[](unsigned int t_index) const override { return this; }
};

template<unsigned int N_LAYER>
struct LayeredContext : public Context {
    std::array<Context*, N_LAYER> m_layers;
protected:
    Context *operator[](unsigned int t_index) override {
        return m_layers[t_index];
    }
    const Context *operator[](unsigned int t_index) const override {
        return m_layers[t_index];
    }
public:
    LayeredContext() = default;
    template<class ...Args> explicit LayeredContext(Args& ...t_args) : Context(), m_layers({&t_args...}) {}
    void set(unsigned int t_layer, Context& t_value) { m_layers[t_layer] = &t_value; }
};

#endif //STATE_MACHINE_CPP_CONTEXT_H
