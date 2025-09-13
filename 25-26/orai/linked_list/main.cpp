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

    void DebugPrint(){
        Node<T>* cur = this->head.next;
        while(cur != &this->head){
            std::cout << cur->value << '\n';
            cur = cur->next;
        }
        std::cout << std::endl;
    }

    Node<T>* Add(T new_value){
        ++this->size;
        return new Node<T>(head.prev, new_value, &head);
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

    size_t Size(){
        return this->size;
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

    void RemoveAt(const size_t& index){
        if(index >= size){
            throw std::out_of_range("LinkedList: Index out of range");
            return;
        }

        Node<T>* cur = this->head.next;
        for(size_t i = 0; i < index; ++i) cur = cur->next;
        cur->Delete();
        --this->size;
    }
};

int main(void){
    LinkedList<int> linkl;

    for(int i = 0; i < 11; ++i) linkl.Add(i);

    linkl.DebugPrint();

    return 0;
}
