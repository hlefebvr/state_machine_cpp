//
// Created by henri on 21/04/21.
//

#ifndef STATE_MACHINE_CPP_COMPARABLE_H
#define STATE_MACHINE_CPP_COMPARABLE_H

namespace Util {
    template<class T> class comparable;
}

template<class T>
class Util::comparable {
protected:
    virtual bool equals_to(const T& t_rhs) const = 0;
public:
    bool operator==(const T& t_rhs) const { return equals_to(t_rhs); }
    bool operator!=(const T& t_rhs) const { return !equals_to(t_rhs); }
};

#endif //STATE_MACHINE_CPP_COMPARABLE_H
