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

    void Delink(){
        if(prev && next && prev != this && next != this){
            this->prev->next = this->next;
            this->next->prev = this->prev;
        }
        this->prev = nullptr;
        this->next = nullptr;
    }
};

template<typename T>
class LinkedList{
private:
    Node<T> head;

public:
    LinkedList() = default;

    ~LinkedList(){
        this->Clear();
    }

    void Add(T new_value){
        new Node<T>(head.prev, new_value, &head);
    }

    void Clear(){
        Node<T>* cur = head.next;
        while(cur != head){
            Node<T> *next = cur->next;
            delete cur;
            cur = next;
        }
        head.next = &head;
        head.prev = &head;
    }
};

int main(void){
    

    return 0;
}
