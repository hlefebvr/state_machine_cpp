//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_H
#define STATE_MACHINE_CPP_CONTEXT_H

#include "AbstractContext.h"

template<class ...Args>
struct InitialContext : public Context, public Pointer<Args>... {

    InitialContext() : Pointer<Args>()... {} // NOLINT(modernize-use-equals-default)
    explicit InitialContext(Args& ...t_args) : Pointer<Args>(&t_args)... {}

    template<class T> void set(T& t_value) { Pointer<T>::operator=(&t_value); }
    using Context::get;
};

#endif //STATE_MACHINE_CPP_CONTEXT_H
