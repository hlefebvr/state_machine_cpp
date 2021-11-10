//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_CONTEXT_2_H
#define STATE_MACHINE_CPP_CONTEXT_2_H


#include "merge.h"

namespace state_machine_cpp {
    class Context2;
}

class state_machine_cpp::Context2 {
    AbstractContextTree& m_underlying_context;
public:

    Context2(AbstractContextTree& t_underlying_context) : m_underlying_context(t_underlying_context) {}

    template<class T> T& get(unsigned int t_layer = 0) {
        return *dynamic_cast<std::shared_ptr<T>&>(m_underlying_context.layer(t_layer)).get();
    }

    template<class T> const T& get(unsigned int t_layer = 0) const {
        return const_cast<Context2&>(*this).get<T>(t_layer);
    }

    template<class ...X, class ...Y>
    static merge_t<ContextTree<X...>, ContextTree<Y...>> join(ContextTree<X...>&& t_x, ContextTree<Y...>&& t_y) {
        merge_t<ContextTree<X...>, ContextTree<Y...>> result;
        Impl::merge<std::tuple<X...>, ContextTree<X...>>::to(&t_x, result);
        Impl::merge<std::tuple<Y...>, ContextTree<Y...>>::to(&t_y, result);
        return result;
    }

};

#endif //STATE_MACHINE_CPP_CONTEXT_2_H
