//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_H
#define STATE_MACHINE_CPP_CONTEXT_H

#include "Pointer.h"

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

#endif //STATE_MACHINE_CPP_CONTEXT_H
