//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_STATEINSTANCE_H
#define STATE_MACHINE_CPP_STATEINSTANCE_H

#include <string>
#include <stdexcept>

#include "../utils/comparable.h"

template<class> class hash;

namespace State {
    class Id;
    class Instance;
}

std::ostream& operator<<(std::ostream& t_os, const State::Instance& t_id);

class State::Instance : public Util::comparable<State::Instance> {

    const State::Id* m_id = nullptr;
    unsigned int m_level = 0;
    std::size_t m_hash = 0;

    void update_hash();
    friend struct hash<State::Instance>;
protected:
    bool equals_to(const Instance &t_rhs) const override;
public:
    Instance() = default;
    Instance(const Id& t_id, unsigned int t_level);
    Instance(const Id& t_id); // NOLINT(google-explicit-constructor)
    Instance& operator=(const Id& t_rhs);
    Instance& operator=(const Instance&) = default;

    std::string name() const;
    inline const State::Id& id() const;
};

const State::Id &State::Instance::id() const {
    if (!m_id) {
        throw std::runtime_error("Trying to get State::Id on an undefined state.");
    }
    return *m_id;
}



#endif //STATE_MACHINE_CPP_STATEINSTANCE_H
