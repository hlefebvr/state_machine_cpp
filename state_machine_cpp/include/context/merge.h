//
// Created by henri on 10/11/21.
//

#ifndef STATE_MACHINE_CPP_MERGE_H
#define STATE_MACHINE_CPP_MERGE_H


#include <cassert>
#include "abstract_attribute_tree.h"

namespace state_machine_cpp {
    class AbstractLayer;

    template<class ...> class AttributeTree;

    template<class ...> class Layer;
}

//////////////////////////// MERGE TYPE ////////////////////////////////////

namespace state_machine_cpp::Impl {

    template<class ...>
    struct merge_layers;

    template<class ...X, class ...Y>
    struct merge_layers<Layer<X...>, Layer<Y...>> {
        using type = Layer<X..., Y...>;
    };

    template<class ...>
    struct merge_t;

    template<class A>
    struct merge_t<A, AttributeTree<>, AttributeTree<>> {
        using type = A;
    };

    template<class ...A, class HX, class ...QX>
    struct merge_t<AttributeTree<A...>, AttributeTree<HX, QX...>, AttributeTree<>> {
        using type = typename merge_t<
                AttributeTree<A..., HX>,
                AttributeTree<QX...>,
                AttributeTree<>
        >::type;
    };

    template<class ...A, class HY, class ...QY>
    struct merge_t<AttributeTree<A...>, AttributeTree<>, AttributeTree<HY, QY...>> {
        using type = typename merge_t<
                AttributeTree<A..., HY>,
                AttributeTree<>,
                AttributeTree<QY...>
        >::type;
    };

    template<class ...A, class HX, class ...QX, class HY, class ...QY>
    struct merge_t<AttributeTree<A...>, AttributeTree<HX, QX...>, AttributeTree<HY, QY...>> {
        using type = typename merge_t<
                AttributeTree<A..., typename merge_layers<HX, HY>::type>,
                AttributeTree<QX...>,
                AttributeTree<QY...>
        >::type;
    };

    //////////////////////////// MERGE ////////////////////////////////////

    template<class ...X> struct merge;

    template<class ...> struct call_merge;

    template<class HY, class ...QY>
    struct call_merge<Layer<HY, QY...>> {

        static void on(Layer<>*, AbstractLayer&) {
            assert(false);
        }

        static void on(Layer<HY, QY...>* t_layer, AbstractLayer& t_destination) {
            merge<std::tuple<HY, QY...>, Layer<HY, QY...>>::to(t_layer, t_destination);
        }

    };

    template<class ...X>
    struct merge<std::tuple<>, AttributeTree<X...>> {

        static void to(AttributeTree<X...>* t_source, AbstractAttributeTree& t_destination, unsigned int t_layer = 0) {}

    };

    template<class HX, class ...QX, class ...X>
    struct merge<std::tuple<HX, QX...>, AttributeTree<X...>> {

        static void to(AttributeTree<X...>* t_source, AbstractAttributeTree& t_destination, unsigned int t_layer = 0) {
            if constexpr (!std::is_same_v<HX, Layer<>>) {
                auto &layer = dynamic_cast<HX &>(((AbstractAttributeTree *) t_source)->layer(t_layer));
                call_merge<HX>::on(&layer, t_destination.layer(t_layer));
            }
            merge<std::tuple<QX...>, AttributeTree<X...>>::to(t_source, t_destination, t_layer + 1);
        }

    };

    template<class ...X>
    struct merge<std::tuple<>, Layer<X...>> {

        static void to(Layer<X...>* t_source, AbstractLayer& t_destination) {}

    };

    template<class HX, class ...QX, class ...X>
    struct merge<std::tuple<HX, QX...>, Layer<X...>> {

        static void to(Layer<X...>* t_source, AbstractLayer& t_destination) {
            dynamic_cast<std::shared_ptr<HX>&>(t_destination).swap(dynamic_cast<std::shared_ptr<HX>&>(*t_source));
            merge<std::tuple<QX...>, Layer<X...>>::to(t_source, t_destination);
        }

    };

}

namespace state_machine_cpp {

    template<class ...T> using merge_t = typename Impl::merge_t<AttributeTree<>, T...>::type;

}


#endif //STATE_MACHINE_CPP_MERGE_H
