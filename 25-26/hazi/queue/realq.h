#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

template <typename T, size_t N>
class real_queue {
  private:
    std::array<T, N> array_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;

  public:
    real_queue() = default;
    real_queue(const T& value);

    const T& back() const;
    T& back();
    const T& front() const;
    T& front();

    void push(const T& value);
    void push(T&& value);
    void pop();

    size_t size() const;
    bool empty() const;
    size_t capacity() const;
};

template <typename T, size_t N>
real_queue<T, N>::real_queue(const T& value) {
    for(size_t i = 0; i < N; ++i) {
        push(value);
    }
}

template <typename T, size_t N>
const T& real_queue<T, N>::back() const {
    if(size_ == 0) {
        throw std::runtime_error("yo, the queue is empty");
    }
    return array_[(tail_ + N - 1) % N];
}

template <typename T, size_t N>
T& real_queue<T, N>::back() {
    if(size_ == 0) {
        throw std::runtime_error("yo, the queue is empty");
    }
    return array_[(tail_ + N - 1) % N];
}

template <typename T, size_t N>
const T& real_queue<T, N>::front() const {
    if(size_ == 0) {
        throw std::runtime_error("yo, the queue is empty");
    }
    return array_[head_];
}

template <typename T, size_t N>
T& real_queue<T, N>::front() {
    if(size_ == 0) {
        throw std::runtime_error("yo, the queue is empty");
    }
    return array_[head_];
}

template <typename T, size_t N>
void real_queue<T, N>::push(const T& value) {
    if(size_ == N) {
        throw std::runtime_error("yo, the queue is full");
    }
    array_[tail_] = value;
    tail_ = (tail_ + 1) % N;
    size_++;
}

template <typename T, size_t N>
void real_queue<T, N>::push(T&& value) {
    if(size_ == N) {
        throw std::runtime_error("yo, the queue is full");
    }
    array_[tail_] = std::move(value);
    tail_ = (tail_ + 1) % N;
    size_++;
}

template <typename T, size_t N>
void real_queue<T, N>::pop() {
    if(size_ == 0) {
        throw std::runtime_error("yo, the queue is empty");
    }
    head_ = (head_ + 1) % N;
    --size_;
}

template <typename T, size_t N>
size_t real_queue<T, N>::size() const {
    return size_;
}

template <typename T, size_t N>
bool real_queue<T, N>::empty() const {
    return size_ == 0;
}

template <typename T, size_t N>
size_t real_queue<T, N>::capacity() const {
    return N;
}
