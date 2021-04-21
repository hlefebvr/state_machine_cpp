//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_STATEID_H
#define STATE_MACHINE_CPP_STATEID_H

#include <string>

#include "StateInstance.h"
#include "constexpr_id.h"
#include "../utils/comparable.h"

namespace State {
    struct Id;
}

struct State::Id : public Util::comparable<State::Id> {
    const std::string m_name;
    const std::size_t m_id;
protected:
    inline bool equals_to(const Id &t_rhs) const override;
public:
    explicit Id(const char *t_name) noexcept;

    Id(const Id&) = delete;
    Id(Id&&) = delete;
    Id& operator=(const Id&) = delete;
    Id& operator=(Id&&) = delete;

    inline const std::string& name() const;
    inline std::size_t id() const;
};

const std::string &State::Id::name() const { return m_name; }
std::size_t State::Id::id() const { return m_id; }
bool State::Id::equals_to(const State::Id &t_rhs) const { return m_id == t_rhs.m_id; }

std::ostream& operator<<(std::ostream& t_os, const State::Id& t_id);

#endif //STATE_MACHINE_CPP_STATEID_H
