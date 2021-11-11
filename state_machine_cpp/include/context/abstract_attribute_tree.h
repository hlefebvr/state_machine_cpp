//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_ABSTRACT_ATTRIBUTE_TREE_H
#define STATE_MACHINE_CPP_ABSTRACT_ATTRIBUTE_TREE_H

namespace state_machine_cpp {
    class AbstractLayer;
    class AbstractAttributeTree;

    namespace Impl {
        template<class ...X> struct merge;
    }
}

class state_machine_cpp::AbstractAttributeTree {
protected:
    friend class Context;
    template<class ...X> friend struct Impl::merge;

    virtual AbstractLayer& layer(unsigned int t_i) = 0;

    [[nodiscard]] virtual const AbstractLayer& layer(unsigned int t_i) const {
        return const_cast<AbstractAttributeTree&>(*this).layer(t_i);
    }

public:

    virtual ~AbstractAttributeTree() = default;

};


#endif //STATE_MACHINE_CPP_ABSTRACT_ATTRIBUTE_TREE_H
