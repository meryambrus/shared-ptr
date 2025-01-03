//
// Created by Ambrus on 2024. 10. 03..
//

#ifndef REFCOUNTED_H
#define REFCOUNTED_H

#include <iostream>
#include <ostream>
#include <type_traits>
#include <utility>


class RefCounted {
    template<typename T>
    friend class SharedPtr;

    friend class Tester;
private:
    mutable int refCount = 0;

protected:
    //only derived classes can create an instance of this class
    RefCounted() = default;

    RefCounted(const RefCounted& rhs) {

    }

    RefCounted& operator=(const RefCounted& rhs) {
        return *this;
    }

    RefCounted(RefCounted&& rhs) noexcept {
        refCount = rhs.refCount;
        rhs.refCount = 0;
    }

    RefCounted& operator=(RefCounted&& rhs) noexcept {
        refCount = rhs.refCount;
        rhs.refCount = 0;

        return *this;
    }

    virtual ~RefCounted() = default;
};


template<typename T>
class SharedPtr final {
private:
    //mutable so we can set this to nullptr in case it gets deleted
    mutable T* ptr = nullptr;

    friend class Tester;
    template<typename U>
    friend class SharedPtr;
public:
    SharedPtr() = default;

    template<typename U = T, typename = std::enable_if_t<std::is_base_of<RefCounted, U>::value>>
    explicit SharedPtr(T* ptr = nullptr) : ptr(ptr) {
        increment();
    }

    SharedPtr(const SharedPtr& rhs) {
        ptr = rhs.ptr;
        increment();
    }

    template<typename U, typename = std::enable_if_t<std::is_base_of<T, U>::value>>
    SharedPtr(const SharedPtr<U>& rhs) {
        ptr = rhs.ptr;
        increment();
    }

    SharedPtr& operator=(const SharedPtr& rhs) {
        if (this != &rhs) {
            decrement();

            ptr = rhs.ptr;
            increment();
        }
        return *this;
    }

    template<typename U, typename = std::enable_if_t<std::is_base_of<T, U>::value>>
    SharedPtr& operator=(const SharedPtr<U>& rhs) {
        //this and rhs can't be the same, because then the other copy assignment operator would be called
        decrement();

        ptr = rhs.ptr;
        increment();
        return *this;
    }

    SharedPtr(SharedPtr&& rhs) noexcept {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }

    template<typename U, typename = std::enable_if_t<std::is_base_of<T, U>::value>>
    SharedPtr(SharedPtr<U>&& rhs) noexcept {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& rhs) noexcept {
        if (this != &rhs) {
            decrement();

            ptr = rhs.ptr;
            rhs.ptr = nullptr;
        }
        return *this;
    }

    template<typename U, typename = std::enable_if_t<std::is_base_of<T, U>::value>>
    SharedPtr& operator=(SharedPtr<U>&& rhs) noexcept {
        decrement();

        ptr = rhs.ptr;
        rhs.ptr = nullptr;

        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const noexcept {
        return ptr;
    }

    ~SharedPtr() {
        decrement();
    }

private:
    void increment() const noexcept {
        if (ptr) {
            ++(ptr->RefCounted::refCount);
        }
    }
    void decrement() const noexcept {
        if (ptr) {
            --(ptr->RefCounted::refCount);
            if (ptr->RefCounted::refCount == 0) {
                delete ptr;
                ptr = nullptr;
            }
        }
    }
};

template<typename T, typename... Args>
std::enable_if_t<std::is_base_of<RefCounted, T>::value, SharedPtr<T>>
make_refcounted(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
std::enable_if_t<std::is_base_of<RefCounted, T>::value, SharedPtr<T>>
make_refcounted(T* ptr) {
    return SharedPtr<T>(ptr);
}

#endif //REFCOUNTED_H
