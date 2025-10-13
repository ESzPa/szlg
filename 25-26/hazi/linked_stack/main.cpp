// 
// Linked Stack implementation for the 2025-10-17 homework
// C++17 compatible 
//
#include <iostream>
#include <stdexcept>
#include <memory>

template<typename T>
struct Node {
    T value;
    std::unique_ptr<Node<T>> bottom;

    Node(const T& val, std::unique_ptr<Node<T>> btm = nullptr)
        : value(val), bottom(std::move(btm)) {}
};

template<typename T>
class LinkedStack {
private:
    std::unique_ptr<Node<T>> head;
    size_t ssize;

public:
    LinkedStack() : head(nullptr), ssize(0) {}
    ~LinkedStack() = default;

    void push(const T& value) {
        this->head = std::make_unique<Node<T>>(value, this->head);
        ++this->ssize;
    }

    void push(T&& value) {
        this->head = std::make_unique<Node<T>>(std::move(value), std::move(this->head));
        ++this->ssize;
    }

    void pop() {
        if(!this->head) {
            throw std::runtime_error("Stack is empty");
        }
        this->head = std::move(head->bottom);
        --this->ssize;
    }

    T& top() {
        if(!this->head) {
            throw std::runtime_error("Stack is empty");
        }
        return head->value;
    }

    bool empty() { return this->ssize == 0; }
    size_t size() { return this->ssize; }

    // Homework solution starts here

    // 1.
    template<typename Predicate>
    LinkedStack Where(Predicate pred) const {
        LinkedStack st;
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)){
                st.push(cur->value);
            }
            cur = cur->bottom.get();
        }
        return st;
    }

    // 2.
    template<typename Selector>
    LinkedStack Select(Selector select) const {
        LinkedStack st;
        Node<T>* cur = this->head.get();
        while(cur) {
            st.push(select(cur->value));
            cur = cur->bottom.get();
        }
        return st;
    }

    // 3.
    LinkedStack Reverse() const {
        LinkedStack st;
        Node<T>* cur = this->head.get();
        while(cur) {
            st.push(cur->value);
            cur = cur->bottom.get();
        }
        return st;
    }

    // 4.
    template<typename Predicate>
    T First(Predicate pred) const {
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)){
                return cur->value;
            }
            cur = cur->bottom.get();
        }
        return T();
    }

    // 5.
    template<typename Predicate>
    bool Contains(Predicate pred) const {
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)) return true;
            cur = cur->bottom.get();
        }
        return false;
    }

    // 6.
    template<typename Predicate>
    size_t Count(Predicate pred) const {
        size_t count = 0;
        Node<T>* cur = this->head.get();
        while(cur) {
            if(pred(cur->value)) ++count;
            cur = cur->bottom.get();
        }
        return count;
    }

    // 7.
    template<typename Comparator>
    T Max(Comparator comp) const {
        if(!this->ssize) throw std::runtime_error("Stack is empty");
        Node<T>* cur = this->head.get();
        T max = cur->value;
        cur = cur->bottom.get();
        while(cur) {
            if(comp(max, cur->value) < 0) max = cur->value; 
            cur = cur->bottom.get();
        }
        return max;
    }
};

int main(void) {
    while(1) std::cout << "Testswhere?\n";

    return 0;
}
