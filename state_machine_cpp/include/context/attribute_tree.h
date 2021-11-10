//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_ATTRIBUTE_TREE_H
#define STATE_MACHINE_CPP_ATTRIBUTE_TREE_H

#include <array>
#include <memory>

#include "abstract_attribute_tree.h"
#include "layer.h"

namespace state_machine_cpp {
    template<class ...T> class AttributeTree;
}

template<class HT, class ...QT>
class state_machine_cpp::AttributeTree<HT, QT...> : public AbstractAttributeTree {

    std::array<std::shared_ptr<AbstractLayer>, sizeof...(QT) + 1> m_layers;

    template<unsigned int N, class ...HX, class ...QX>
    void initialize(Layer<HX...>* t_head, QX* ...t_queue) {
        m_layers[N].reset(t_head);
        if constexpr (sizeof...(QX) > 0) {
            initialize<N + 1>(t_queue...);
        }
    }

protected:

    AbstractLayer& layer(unsigned int t_i) override {
        return *m_layers[t_i].get();
    }

public:
    AttributeTree() : m_layers({std::make_shared<HT>(), std::make_shared<QT>()... }) {  }

    AttributeTree(HT* t_head, QT* ...t_queue) {
        initialize<0>(t_head, t_queue...);
    }

};


#endif //STATE_MACHINE_CPP_ATTRIBUTE_TREE_H
