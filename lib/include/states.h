//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_STATES_H
#define STATE_MACHINE_CPP_STATES_H

#include <stdexcept>
#include <string>
#include "__comparable.h"

namespace state_machine_cpp {
    template<class> class hash;

    namespace State {
        struct Id;
        class Instance;
        class Any;
    }
}

std::ostream& operator<<(std::ostream& t_os, const state_machine_cpp::State::Id& t_id);
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

struct state_machine_cpp::State::Id : public Util::comparable<State::Id> {
    const std::string m_name;
    const std::size_t m_hash;

    friend class hash<State::Id>;
protected:
    inline bool equals_to(const Id &t_rhs) const override;
public:
    explicit Id(const char *t_name) noexcept;

    Id(const Id&) = delete;
    Id(Id&&) = delete;
    Id& operator=(const Id&) = delete;
    Id& operator=(Id&&) = delete;

    inline const std::string& name() const;
    inline State::Instance operator[](unsigned int t_layer) const;
};

const std::string &state_machine_cpp::State::Id::name() const {
    return m_name;
}

bool state_machine_cpp::State::Id::equals_to(const State::Id &t_rhs) const {
    return m_hash == t_rhs.m_hash;
}

state_machine_cpp::State::Instance state_machine_cpp::State::Id::operator[](unsigned int t_layer) const {
    return State::Instance(*this, t_layer);
}

const state_machine_cpp::State::Id &state_machine_cpp::State::Instance::id() const {
    if (!m_id) {
        throw std::runtime_error("Trying to get State::Id on an undefined state.");
    }
    return *m_id;
}

unsigned int state_machine_cpp::State::Instance::layer() const {
    return m_layer;
}


class state_machine_cpp::State::Any {
    State::Instance m_instance;
    bool m_is_instantiated;

    bool is_instantiated() const { return m_is_instantiated; }
    const State::Instance& as_provided() const { return m_instance; }
    State::Instance instantiate(unsigned int t_layer) const { return m_instance.id()[t_layer]; }
public:
    Any(const State::Id& t_id) // NOLINT(google-explicit-constructor)
            : m_instance(t_id), m_is_instantiated(false) {}
    Any(const State::Instance& t_instance) // NOLINT(google-explicit-constructor)
            : m_instance(t_instance), m_is_instantiated(true) {}

    State::Instance as_instance(unsigned int t_layer_if_not_set) const;
};

#endif //STATE_MACHINE_CPP_STATES_H
