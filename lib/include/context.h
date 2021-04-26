//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_H
#define STATE_MACHINE_CPP_CONTEXT_H

#include "__pointer.h"

class Context {
public:
    virtual ~Context() = default;

    template<class T> T& get() {
        auto* ptr = dynamic_cast<Pointer<T>*>(this);
        if (ptr == nullptr) {
            throw std::runtime_error("Context could not be casted so as to return the desired type");
        }
        return **ptr;
    }

    template<class T> const T& get() const {
        auto* ptr = dynamic_cast<const Pointer<T>*>(this);
        if (ptr == nullptr) {
            throw std::runtime_error("Context could not be casted so as to return the desired type");
        }
        return **ptr;
    }

};

template<class ...Args>
struct InitialContext : public Context, public Pointer<Args>... {

    InitialContext() : Pointer<Args>()... {} // NOLINT(modernize-use-equals-default)
    explicit InitialContext(Args& ...t_args) : Pointer<Args>(&t_args)... {}

    template<class T> void set(T& t_value) { Pointer<T>::operator=(&t_value); }
    using Context::get;
};

#endif //STATE_MACHINE_CPP_CONTEXT_H
