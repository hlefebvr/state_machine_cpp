//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_SIMPLE_H
#define STATE_MACHINE_CPP_CONTEXT_SIMPLE_H

#include "context.h"

namespace state_machine_cpp {
    template<class ...Args> class SimpleContext;
}

template<class ...Args>
class state_machine_cpp::SimpleContext : public Context, public Pointer<Args>... {
public:
    SimpleContext() : Pointer<Args>()... {} // NOLINT(modernize-use-equals-default)
    explicit SimpleContext(Args& ...t_args) : Pointer<Args>(&t_args)... {}

    template<class T> void set(T& t_value) { Pointer<T>::operator=(&t_value); }
    using Context::get;
protected:
    Context *operator[](unsigned int t_index) override { return this; }
    const Context *operator[](unsigned int t_index) const override { return this; }
};


#endif //STATE_MACHINE_CPP_CONTEXT_SIMPLE_H
