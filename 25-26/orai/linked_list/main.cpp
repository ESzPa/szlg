#include <iostream>

template<typename T>
struct Node{
    Node<T>* prev;
    T value;
    Node<T>* next;

    Node() : prev(this), value(T()), next(this) {}

    Node(Node* prev, const T& value, Node* next) : prev(prev), value(value), next(next) {
        prev->next = this;
        next->prev = this;
    }

    Node(Node<T>* prev, const T& value) : Node(prev, value, prev->next) {}

    void Delete(){
        if(prev && next && prev != this && next != this){
            this->prev->next = this->next;
            this->next->prev = this->prev;
        }
        delete this;
    }
};

template<typename T>
class LinkedList{
private:
    Node<T> head;
    size_t size = 0;

public:
    LinkedList() = default;

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    ~LinkedList(){
        this->Clear();
    }

    struct Iterator;
    Iterator begin() { return Iterator(this->head.next); }
    Iterator end() { return Iterator(&this->head); }

    T& operator[](size_t index){
        if(index >= this->size) throw std::out_of_range("LinkedList: Index out of range");
        Node<T>* cur = this->head.next;
        for(size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->value;
    }

    const T& operator[](size_t index) const{
        if(index >= this->size) throw std::out_of_range("LinkedList: Index out of range");
        const Node<T>* cur = this->head.next;
        for(size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->value;
    }

    T& Front() const{
        if(this->head.next == &this->head) throw std::out_of_range("LinkedList: List is empty");
        return this->head.next->value;
    }

    T& Back() const{
        if(this->head.prev == &this->head) throw std::out_of_range("LinkedList: List is empty");
        return this->head.prev->value;
    }

    void DebugPrint(){
        for(auto it = this->begin(); it != this->end(); ++it){
            std::cout << *it << '\n';
        }
        std::cout << std::endl;
    }

    T& Add(T new_value){
        ++this->size;
        Node<T>* node = new Node<T>(head.prev, new_value, &head);
        return node->value;
    }

    void Clear(){
        Node<T>* cur = head.next;
        while(cur != &this->head){
            Node<T> *next = cur->next;
            cur->Delete();
            cur = next;
        }
        head.next = &head;
        head.prev = &head;
        this->size = 0;
    }

    size_t Size() const{
        return this->size;
    }

    bool Empty() const{
        return (this->size == 0);
    }

    void Remove(const T& value){
        Node<T>* cur = this->head.next;
        while(cur != &this->head){
            if(cur->value == value){
                cur->Delete();
                --this->size;
                break;
            }
            cur = cur->next;
        }
    }

    void RemoveAll(const T& value){
        Node<T>* cur = this->head.next;
        while(cur != &this->head){
            Node<T>* next = cur->next;
            if(cur->value == value){
                cur->Delete();
                --this->size;
            }
            cur = next;
        }
    }

    void RemoveAt(size_t index){
        if(index >= size) throw std::out_of_range("LinkedList: Index out of range");
        Node<T>* cur = this->head.next;
        for(size_t i = 0; i < index; ++i) cur = cur->next;
        cur->Delete();
        --this->size;
    }
};

template<typename T>
struct LinkedList<T>::Iterator{
    Node<T>* node;

    Iterator(Node<T>* n) : node(n) {}

    T& operator*() const { return node->value; }

    Iterator& operator++(){
        node = node->next;
        return *this;
    }

    Iterator operator++(int){
        Iterator tmp = *this;
        node = node->next;
        return tmp;
    }

    Iterator& operator--(){
        node = node->prev;
        return *this;
    }

    Iterator operator--(int){
        Iterator tmp = *this;
        node = node->prev;
        return tmp;
    }

    bool operator==(const Iterator& other) const { return node == other.node; }
    
    bool operator!=(const Iterator& other) const { return node != other.node; }
};

int main(void){
    LinkedList<int> linkl;

    for(int i = 0; i < 11; ++i) linkl.Add(i);

    linkl[4] = 69;

    linkl.DebugPrint();

    return 0;
}
