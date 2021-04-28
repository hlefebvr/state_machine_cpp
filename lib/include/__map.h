//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP___MAP_H
#define STATE_MACHINE_CPP___MAP_H

#include <memory>

#if __has_include(<robin_hood/robin_hood.h>)
#include <robin_hood/robin_hood.h>
namespace state_machine_cpp {
    namespace map_ns = robin_hood;
}
#else
#include <unordered_map>
namespace state_machine_cpp {
    namespace map_ns = std;
}
#endif

#include "transition_any.h"

namespace state_machine_cpp {
    class TransitionSet;
    namespace State {
        class Instance;
    }
    namespace Transition {
        class Any;
    }
}

class state_machine_cpp::TransitionSet {
public:
    using Set = map_ns::unordered_map<std::size_t , Transition::Any>;

    TransitionSet() = default;

    class iterator {
        Set::iterator m_it;
        explicit iterator(Set::iterator&& t_it) : m_it(t_it) {}
        friend class TransitionSet;
    public:
        void operator++() { ++m_it; }
        bool operator!=(const iterator& t_rhs) const { return m_it != t_rhs.m_it; }
        bool operator==(const iterator& t_rhs) const { return m_it == t_rhs.m_it; }
        Transition::Any& operator*() { return m_it->second; }
        Transition::Any* operator->() { return &m_it->second; }
        const Transition::Any& operator*() const { return m_it->second; }
        const Transition::Any* operator->() const { return &m_it->second; }
    };

    class const_iterator {
        Set::const_iterator m_it;
        explicit const_iterator(Set::const_iterator&& t_it) : m_it(t_it) {}
        friend class TransitionSet;
    public:
        void operator++() { ++m_it; }
        bool operator==(const const_iterator& t_rhs) const { return m_it == t_rhs.m_it; }
        bool operator!=(const const_iterator& t_rhs) const { return m_it != t_rhs.m_it; }
        const Transition::Any& operator*() const { return m_it->second; }
        const Transition::Any* operator->() const { return &m_it->second; }
    };


    void add(const State::Instance& t_instance);
    void remove(const State::Instance& t_instance);
    bool has(const State::Instance& t_instance) const;
    Transition::Any& operator[](const State::Instance& t_instance);
    const Transition::Any& operator[](const State::Instance& t_instance) const;
    iterator find(const State::Instance& t_instance);
    const_iterator find(const State::Instance& t_instance) const;
    bool empty() const;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_iterator begin() const;
    const_iterator end() const;

private:
    Set m_transitions;
};

#endif //STATE_MACHINE_CPP___MAP_H
