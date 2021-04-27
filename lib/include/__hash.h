//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP___HASH_H
#define STATE_MACHINE_CPP___HASH_H

namespace state_machine_cpp {
    template<class T>
    struct hash {
        static std::size_t get(const T &t_x) {
            return t_x.m_hash;
        }
    };
}

#endif //STATE_MACHINE_CPP___HASH_H
