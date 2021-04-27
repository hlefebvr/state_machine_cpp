//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_STATE_INSTANCE_H
#define STATE_MACHINE_CPP_STATE_INSTANCE_H

#include <iostream>
#include "__comparable.h"

namespace state_machine_cpp {
    template<class> class hash;

    namespace State {
        class Instance;
        class Id;
    }
}


std::ostream& operator<<(std::ostream& t_os, const state_machine_cpp::State::Instance& t_id);

class state_machine_cpp::State::Instance : public Util::comparable<State::Instance> {

    const State::Id* m_id = nullptr;
    unsigned int m_layer = 0;
    std::size_t m_hash = 0;

    void update_hash();
    friend struct hash<State::Instance>;
protected:
    bool equals_to(const Instance &t_rhs) const override;
public:
    Instance() = default;
    Instance(const Id& t_id, unsigned int t_layer);
    Instance(const Id& t_id); // NOLINT(google-explicit-constructor)
    Instance& operator=(const Id& t_rhs);
    Instance& operator=(const Instance&) = default;

    std::string name() const;
    inline const State::Id& id() const;
    inline unsigned int layer() const;
};

const state_machine_cpp::State::Id &state_machine_cpp::State::Instance::id() const {
    if (!m_id) {
        throw std::runtime_error("Trying to get State::Id on an undefined state.");
    }
    return *m_id;
}

unsigned int state_machine_cpp::State::Instance::layer() const {
    return m_layer;
}


#endif //STATE_MACHINE_CPP_STATE_INSTANCE_H
