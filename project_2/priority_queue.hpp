#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <iostream>

template <typename T, typename P>
struct element {
    T value;
    P priority;

    operator T() const {
        return value;
    }

    bool operator<(const element& other) const {
        return priority < other.priority;
    }

    bool operator<=(const element& other) const {
        return priority <= other.priority;
    }

    bool operator==(const element& other) const {
        return value == other.value;
    }
};

template <typename T, typename P>
std::ostream& operator<<(std::ostream& os, const element<T, P>& e) {
    return os << e.value << "(" << e.priority << ")";
}

template <typename T, typename P>
class PriorityQueue {
public:
    virtual void push(element<T, P> value) = 0;
    virtual T pop() = 0;
    virtual T peek() = 0;
    virtual size_t size() = 0;
    virtual void modify(T value, P new_priority) = 0;
    virtual void print() = 0;
};

#endif