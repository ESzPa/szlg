#pragma once

#include <array>

template <typename T, std::size_t N>
class array_1 {
  private:
    typedef std::size_t size_type_;
    std::array<T, N> array_;

    size_type_ index_(size_type_ index) const {
        return index - 1;
    }

  public:
    typedef T value_type;
    typedef size_type_ size_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

    typedef typename std::array<value_type, N>::iterator iterator;
    typedef typename std::array<value_type, N>::const_iterator const_iterator;
    typedef typename std::array<value_type, N>::reverse_iterator reverse_iterator;
    typedef typename std::array<value_type, N>::const_reverse_iterator const_reverse_iterator;

    // Element access

    reference at(size_type pos) {
        return array_.at(index_(pos));
    }

    const_reference at(size_type pos) const {
        return array_.at(index_(pos));
    }

    reference operator[](size_type pos) {
        return array_[index_(pos)];
    }

    const_reference operator[](size_type pos) const {
        return array_[index_(pos)];
    }

    reference front() {
        return array_.front();
    }

    const_reference front() const {
        return array_.front();
    }

    reference back() {
        return array_.back();
    }

    const_reference back() const {
        return array_.back();
    }

    pointer data() noexcept {
        return array_.data();
    }

    const_pointer data() const noexcept {
        return array_.data();
    }

    // Iterators

    iterator begin() noexcept {
        return array_.begin();
    }

    const_iterator begin() const noexcept {
        return array_.begin();
    }

    const_iterator cbegin() const noexcept {
        return array_.cbegin();
    }

    iterator end() noexcept {
        return array_.end();
    }

    const_iterator end() const noexcept {
        return array_.end();
    }

    const_iterator cend() const noexcept {
        return array_.cend();
    }

    reverse_iterator rbegin() noexcept {
        return array_.rbegin();
    }

    const_reverse_iterator rbegin() const noexcept {
        return array_.rbegin();
    }

    const_reverse_iterator crbegin() const noexcept {
        return array_.crbegin();
    }

    reverse_iterator rend() noexcept {
        return array_.rend();
    }

    const_reverse_iterator rend() const noexcept {
        return array_.rend();
    }

    const_reverse_iterator crend() const noexcept {
        return array_.crend();
    }

    // Capacity

    constexpr bool empty() const noexcept {
        return array_.empty();
    }

    constexpr size_type size() const noexcept {
        return array_.size();
    }

    constexpr size_type max_size() const noexcept {
        return N;
    }

    // Operations

    void fill(const_reference value) {
        array_.fill(value);
    }

    void swap(array_1& other) noexcept {
        array_.swap(other.array_);
    }
};
