//
// Created by henri on 04/05/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_AUTO_H
#define STATE_MACHINE_CPP_CONTEXT_AUTO_H

#include <memory>
#include <vector>
#include "context.h"

namespace state_machine_cpp {
    template<class ...T> class AutoContext;
}

template<class ...T>
class state_machine_cpp::AutoContext : public state_machine_cpp::Context {
    struct AbstractPointer {
        virtual ~AbstractPointer() = default;
    };
    template<class S> struct Pointer : public AbstractPointer {
        S* value;
        explicit Pointer(S* t_ptr) : value(t_ptr) {}
        ~Pointer() override { delete value; }
    };
    std::vector<AbstractPointer*> m_attributes;
    std::unique_ptr<Context> m_context;
public:
    explicit AutoContext(T*... t_attributes, Context* t_context);
    ~AutoContext() override;
protected:
    Context *operator[](unsigned int t_index) override;
    const Context *operator[](unsigned int t_index) const override;

};

template<class... T>
state_machine_cpp::AutoContext<T...>::AutoContext(T *... t_attributes, Context *t_context)
    : m_attributes({ new Pointer<T>(t_attributes)... }), m_context(t_context) {

}

template<class... T>
state_machine_cpp::Context *state_machine_cpp::AutoContext<T...>::operator[](unsigned int t_index) {
    return Context::call_square_bracket_operator_on(m_context.get(), t_index);
}

template<class... T>
const state_machine_cpp::Context *state_machine_cpp::AutoContext<T...>::operator[](unsigned int t_index) const {
    return Context::call_square_bracket_operator_on(m_context.get(), t_index);
}

template<class... T>
state_machine_cpp::AutoContext<T...>::~AutoContext() {
    for (auto ptr : m_attributes) {
        delete ptr;
    }
}

#endif //STATE_MACHINE_CPP_CONTEXT_AUTO_H
