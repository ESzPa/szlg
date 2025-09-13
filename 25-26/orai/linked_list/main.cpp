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
    size_t list_size = 0;

    Node<T>* smart_index(size_t index){
        if(index >= this->list_size) throw std::out_of_range("LinkedList: Index out of range");
        if(index < this->list_size/2){
            Node<T>* cur = this->head.next;
            for(size_t i = 0; i < index; ++i) cur = cur->next;
            return cur;
        }
        else{
            Node<T>* cur = this->head.prev;
            for(size_t i = 0; i < this->list_size-index-1; ++i) cur = cur->prev;
            return cur;
        }
    }

public:
    LinkedList() = default;

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    ~LinkedList(){
        this->clear();
    }

    struct Iterator;
    Iterator begin() { return Iterator(this->head.next); }
    Iterator end() { return Iterator(&this->head); }

    T& operator[](size_t index){
        return smart_index(index)->value;
    }
    
    const T& operator[](size_t index) const{
        return smart_index(index)->value;
    }
    
    T& front(){
        if(this->head.next == &this->head) throw std::out_of_range("LinkedList: List is empty");
        return this->head.next->value;
    }

    const T& front() const{
        if(this->head.next == &this->head) throw std::out_of_range("LinkedList: List is empty");
        return this->head.next->value;
    }

    T& back(){
        if(this->head.prev == &this->head) throw std::out_of_range("LinkedList: List is empty");
        return this->head.prev->value;
    }

    const T& back() const{
        if(this->head.prev == &this->head) throw std::out_of_range("LinkedList: List is empty");
        return this->head.prev->value;
    }

    void DebugPrint(){
        for(auto it = this->begin(); it != this->end(); ++it){
            std::cout << *it << '\n';
        }
        std::cout << std::endl;
    }

    void push_back(const T& value){
        new Node<T>(head.prev, value, &head);
        ++this->list_size;
    }

    void insert_at(size_t index, const T& value){
        Node<T>* indexed = smart_index(index);
        Node<T>* node = new Node<T>(indexed, value, indexed->next);
        indexed->next->prev = node;
        indexed->next = node;
        ++this->list_size;
    }

    void clear(){
        Node<T>* cur = head.next;
        while(cur != &this->head){
            Node<T> *next = cur->next;
            cur->Delete();
            cur = next;
        }
        head.next = &head;
        head.prev = &head;
        this->list_size = 0;
    }

    size_t size() const{
        return this->list_size;
    }

    bool empty() const{
        return (this->list_size == 0);
    }

    void remove(const T& value){
        Node<T>* cur = this->head.next;
        while(cur != &this->head){
            if(cur->value == value){
                cur->Delete();
                --this->list_size;
                break;
            }
            cur = cur->next;
        }
    }

    void remove_all(const T& value){
        Node<T>* cur = this->head.next;
        while(cur != &this->head){
            Node<T>* next = cur->next;
            if(cur->value == value){
                cur->Delete();
                --this->list_size;
            }
            cur = next;
        }
    }

    void remove_at(size_t index){
        smart_index(index)->Delete();
        --this->list_size;
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

    for(int i = 0; i < 12; ++i) linkl.push_back(i);

    linkl[3] = 69;
    linkl[8] = 420;

    linkl.remove_at(linkl.size()-1);

    linkl.DebugPrint();

    return 0;
}
