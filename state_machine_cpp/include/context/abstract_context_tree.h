//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_ABSTRACT_CONTEXT_TREE_H
#define STATE_MACHINE_CPP_ABSTRACT_CONTEXT_TREE_H

namespace state_machine_cpp {
    class AbstractLayer;
    class AbstractContextTree;

    namespace Impl {
        template<class ...X> struct merge;
    }
}

class state_machine_cpp::AbstractContextTree {
protected:
    friend class Context;
    template<class ...X> friend struct Impl::merge;

    virtual AbstractLayer& layer(unsigned int t_i) = 0;

    [[nodiscard]] virtual const AbstractLayer& layer(unsigned int t_i) const {
        return const_cast<AbstractContextTree&>(*this).layer(t_i);
    }

};


#endif //STATE_MACHINE_CPP_ABSTRACT_CONTEXT_TREE_H
