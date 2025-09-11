#include <iostream>

template<typename T>
struct Node{
    Node* prev;
    T value;
    Node* next;

    Node(){
        this->prev = this;
        this->value = T();
        this->next = this;
    }

    Node(T value){
        this->prev = this;
        this->value = value;
        this->next = this;
    }
};
