#pragma once

#include <cstddef>
#include <cstring>
#include <vector>

template <typename T>
class dumb_queue {
  private:
    std::vector<T> array_;

  public:
    dumb_queue(size_t N = 256);

    const T& back() const;
    T& back();
    const T& front() const;
    T& front();

    void push(const T& value);
    void push(T&& value);
    void pop();

    size_t size() const;
    bool empty() const;
};

template <typename T>
dumb_queue<T>::dumb_queue(size_t N) {
    array_.reserve(N);
}

template <typename T>
const T& dumb_queue<T>::back() const {
    return array_.back();
}

template <typename T>
T& dumb_queue<T>::back() {
    return array_.back();
}

template <typename T>
const T& dumb_queue<T>::front() const {
    return array_.front();
}

template <typename T>
T& dumb_queue<T>::front() {
    return array_.front();
}

template <typename T>
void dumb_queue<T>::push(const T& value) {
    array_.push_back(value);
}

template <typename T>
void dumb_queue<T>::push(T&& value) {
    array_.push_back(std::move(value));
}

template <typename T>
void dumb_queue<T>::pop() {
    if(array_.empty())
        return;

    if constexpr(std::is_integral_v<T>) {
        if(array_.size() > 1) {
            std::memmove(&array_[0], &array_[1], (array_.size() - 1) * sizeof(T));
        }
        array_.pop_back();
    }
    else {
        array_.erase(array_.begin());
    }
}

template <typename T>
size_t dumb_queue<T>::size() const {
    return array_.size();
}

template <typename T>
bool dumb_queue<T>::empty() const {
    return array_.empty();
}
