#pragma once

#include <vector>

template <typename T>
class vector_1 {
  private:
    typedef std::size_t size_type;

    std::vector<T> vector_;

    size_type index_(size_type index) const {
        return index - 1;
    }

  public:
    //// Member functions

    vector_1(size_type size = 0, const T& fill_val = T()) {
        vector_.resize(size, fill_val);
    }

    vector_1(const vector_1& other) {
        vector_ = other.vector_;
    }

    vector_1(vector_1&& other) {
        vector_ = std::move(other.vector_);
    }

    vector_1& operator=(const vector_1& other) {
        if(this != &other) {
            vector_ = other.vector_;
        }
        return *this;
    }

    vector_1& operator=(vector_1&& other) noexcept {
        if(this != &other) {
            vector_ = std::move(other.vector_);
        }
        return *this;
    }

    /// Element access

    T& at(size_type pos) {
        return vector_.at(index_(pos));
    }

    const T& at(size_type pos) const {
        return vector_.at(index_(pos));
    }

    T& operator[](size_type pos) {
        return vector_[index_(pos)];
    }

    const T& operator[](size_type pos) const {
        return vector_[index_(pos)];
    }

    T& front() {
        return vector_.front();
    }

    const T& front() const {
        return vector_.front();
    }

    T& back() {
        return vector_.back();
    }

    const T& back() const {
        return vector_.back();
    }

    T* data() {
        return vector_.data();
    }

    const T* data() const {
        return vector_.data();
    }

    std::vector<T>& get_container() {
        return vector_;
    }

    const std::vector<T>& get_container() const {
        return vector_;
    }

    /// Iterators

    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    typedef typename std::vector<T>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;

    iterator begin() {
        return vector_.begin();
    }

    const_iterator begin() const {
        return vector_.begin();
    }

    const_iterator cbegin() const {
        return vector_.cbegin();
    }

    iterator end() {
        return vector_.end();
    }

    const_iterator end() const {
        return vector_.end();
    }

    const_iterator cend() const {
        return vector_.cend();
    }

    reverse_iterator rbegin() {
        return vector_.rbegin();
    }

    const_reverse_iterator rbegin() const {
        return vector_.rbegin();
    }

    const_reverse_iterator crbegin() const {
        return vector_.crbegin();
    }

    reverse_iterator rend() {
        return vector_.rend();
    }

    const_reverse_iterator rend() const {
        return vector_.rend();
    }

    const_reverse_iterator crend() const {
        return vector_.crend();
    }

    /// Capacity

    bool empty() const {
        return vector_.empty();
    }

    size_type size() const {
        return vector_.size();
    }

    size_type max_size() const {
        return vector_.max_size();
    }

    void reserve(size_type new_cap) {
        vector_.reserve(new_cap);
    }

    size_type capacity() const {
        return vector_.capacity();
    }

    void shrink_to_fit() {
        vector_.shrink_to_fit();
    }

    /// Modifiers

    void clear() {
        vector_.clear();
    }

    iterator insert(const_iterator pos, const T& value) {
        return vector_.insert(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
        return vector_.insert(pos, std::move(value));
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        return vector_.insert(pos, count, value);
    }

    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        return vector_.insert(pos, first, last);
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        return vector_.insert(pos, ilist);
    }

    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        return vector_.emplace(pos, std::forward<Args>(args)...);
    }

    iterator erase(const_iterator pos) {
        return vector_.erase(pos);
    }

    iterator erase(const_iterator first, const_iterator last) {
        return vector_.erase(first, last);
    }

    void push_back(const T& value) {
        vector_.push_back(value);
    }

    void push_back(T&& value) {
        vector_.push_back(std::move(value));
    }

    template <class... Args>
    void emplace_back(Args&&... args) {
        vector_.emplace_back(std::forward<Args>(args)...);
    }
    void pop_back() {
        vector_.pop_back();
    }

    void resize(size_type count) {
        vector_.resize(count);
    }

    void resize(size_type count, const T& value) {
        vector_.resize(count, value);
    }

    void swap(vector_1& other) noexcept {
        vector_.swap(other.vector_);
    }

    // Non-member functions are not implemented
};
