#pragma once

#include <memory>
#include <stdexcept>

template <typename T>
class linked_queue {
  private:
    struct lq_node {
        T value;
        std::unique_ptr<lq_node> next;

        template <typename U>
        explicit lq_node(U&& value) : value(std::forward<U>(value)), next(nullptr) {
        }
    };

    std::unique_ptr<lq_node> front_;
    lq_node* rear_ = nullptr;
    size_t size_ = 0;

  public:
    linked_queue() = default;

    ~linked_queue() {
        while(!empty()) {
            pop();
        }
    }

    linked_queue(const linked_queue&) = delete;
    linked_queue& operator=(const linked_queue&) = delete;

    linked_queue(linked_queue&& other) noexcept
        : front_(std::move(other.front_)), rear_(other.rear_), size_(other.size_) {
        other.rear_ = nullptr;
        other.size_ = 0;
    }

    linked_queue& operator=(linked_queue&& other) noexcept {
        if(this != &other) {
            while(!empty()) {
                pop();
            }
            front_ = std::move(other.front_);
            rear_ = other.rear_;
            size_ = other.size_;
            other.rear_ = nullptr;
            other.size_ = 0;
        }

        return *this;
    }

    const T& back() const;
    T& back();
    const T& front() const;
    T& front();

    template <typename U>
    void push(U&& value);
    void pop();

    size_t size() const {
        return size_;
    }
    bool empty() const {
        return size_ == 0;
    }
};

template <typename T>
const T& linked_queue<T>::back() const {
    if(empty()) {
        throw std::runtime_error("mate, the queue is empty innit");
    }

    return rear_->value;
}

template <typename T>
T& linked_queue<T>::back() {
    if(empty()) {
        throw std::runtime_error("mate, the queue is empty innit");
    }

    return rear_->value;
}

template <typename T>
const T& linked_queue<T>::front() const {
    if(empty()) {
        throw std::runtime_error("mate, the queue is empty innit");
    }

    return front_->value;
}

template <typename T>
T& linked_queue<T>::front() {
    if(empty()) {
        throw std::runtime_error("mate, the queue is empty innit");
    }

    return front_->value;
}

template <typename T>
template <typename U>
void linked_queue<T>::push(U&& value) {
    auto new_node = std::make_unique<lq_node>(std::forward<U>(value));

    if(empty()) {
        front_ = std::move(new_node);
        rear_ = front_.get();
    }
    else {
        rear_->next = std::move(new_node);
        rear_ = rear_->next.get();
    }

    ++size_;
}

template <typename T>
void linked_queue<T>::pop() {
    if(empty()) {
        throw std::runtime_error("mate, the queue is empty innit");
    }

    if(front_.get() == rear_) {
        front_.reset();
        rear_ = nullptr;
    }
    else {
        front_ = std::move(front_->next);
    }

    --size_;
}
