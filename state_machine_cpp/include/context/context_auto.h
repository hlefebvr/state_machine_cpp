//
// Created by henri on 04/05/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_AUTO_H
#define STATE_MACHINE_CPP_CONTEXT_AUTO_H

#include <memory>
#include <vector>
#include "context.h"

namespace state_machine_cpp {
    class AutoContext;
}

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
    AutoContext() = default;
    template<class ...T> explicit AutoContext(Context* t_context, T*... t_attributes);
    ~AutoContext() override;
protected:
    Context *operator[](unsigned int t_index) override;
    const Context *operator[](unsigned int t_index) const override;

};

template<class... T>
state_machine_cpp::AutoContext::AutoContext(Context *t_context, T *... t_attributes)
        : m_attributes({ new Pointer<T>(t_attributes)... }), m_context(t_context) {

}

#endif //STATE_MACHINE_CPP_CONTEXT_AUTO_H
