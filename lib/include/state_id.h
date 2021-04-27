//
// Created by henri on 27/04/21.
//

#ifndef STATE_MACHINE_CPP_STATE_ID_H
#define STATE_MACHINE_CPP_STATE_ID_H

#include <iostream>
#include "__comparable.h"

namespace state_machine_cpp {
    template<class> class hash;

    namespace State {
        struct Id;
        class Instance;
    }
}


std::ostream& operator<<(std::ostream& t_os, const state_machine_cpp::State::Id& t_id);

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
    State::Instance operator[](unsigned int t_layer) const;
};

const std::string &state_machine_cpp::State::Id::name() const {
    return m_name;
}

bool state_machine_cpp::State::Id::equals_to(const State::Id &t_rhs) const {
    return m_hash == t_rhs.m_hash;
}


#endif //STATE_MACHINE_CPP_STATE_ID_H
