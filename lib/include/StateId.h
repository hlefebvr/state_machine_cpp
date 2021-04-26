//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_STATEID_H
#define STATE_MACHINE_CPP_STATEID_H

#include <string>

#include "StateInstance.h"
#include "comparable.h"

namespace State {
    struct Id;
}

std::ostream& operator<<(std::ostream& t_os, const State::Id& t_id);

struct State::Id : public Util::comparable<State::Id> {
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
    inline State::Instance operator[](unsigned int t_level) const;
};

const std::string &State::Id::name() const {
    return m_name;
}

bool State::Id::equals_to(const State::Id &t_rhs) const {
    return m_hash == t_rhs.m_hash;
}

State::Instance State::Id::operator[](unsigned int t_level) const {
    return State::Instance(*this, t_level);
}

#endif //STATE_MACHINE_CPP_STATEID_H
