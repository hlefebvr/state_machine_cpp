//
// Created by henri on 22/04/21.
//

#ifndef STATE_MACHINE_CPP_POINTER_H
#define STATE_MACHINE_CPP_POINTER_H

template<class T>
class Pointer {
    T* m_value = nullptr;
public:
    Pointer() = default;
    explicit Pointer(T* t_value) : m_value(t_value) {}
    Pointer(const Pointer<T>&) = default;
    Pointer(Pointer<T>&&)  noexcept = default;
    Pointer& operator=(const Pointer<T>&) = default;
    Pointer& operator=(Pointer<T>&&) noexcept = default;
    Pointer& operator=(T* t_value) { m_value = t_value; return *this; }

    T& operator*() { return *m_value; }
    const T& operator*() const { return *m_value; }

    T* operator->() { return m_value; }
    const T* operator->() const { return m_value; }

    explicit operator bool() const { return m_value != nullptr; }
};

#endif //STATE_MACHINE_CPP_POINTER_H
