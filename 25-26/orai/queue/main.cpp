#include <iostream>

template<typename T, size_t N>
class CQueue{
private:
    T array[N];
    size_t _enqueue;
    size_t _dequeue;
    size_t _size;
    size_t _capacity;

public:
    CQueue() : _enqueue(0), _dequeue(0), _size(0), _capacity(N) {}

    void enqueue(T value){
        if(this->_size >= this->_capacity){
            throw std::overflow_error("Queue at max capacity");
        }

        this->array[this->_enqueue] = value;
        ++this->_size;

        if(++this->_enqueue >= this->_capacity){
            this->_enqueue = 0;
        }
    }

    T dequeue(){
        if(this->_size == 0){
            throw std::underflow_error("Queue has no elements to dequeue");
        }

        T value = std::move(this->array[this->_dequeue]);
        --this->_size;

        if(++this->_dequeue >= this->_capacity){
            this->_dequeue = 0;
        }

        return value;
    }

    T& front(){
        if(this->_size == 0){
            throw std::underflow_error("Queue has no front element");
        }

        return this->array[this->_dequeue];
    }

    const T& front() const{
        if(this->_size == 0){
            throw std::underflow_error("Queue has no front element");
        }

        return this->array[this->_dequeue];
    }

    T& back(){
        if(this->_size >= this->_capacity){
            throw std::overflow_error("Queue has no back element");
        }

        size_t index = (this->_enqueue == 0) ? (this->_capacity - 1) : (this->_enqueue - 1);
        return this->array[index];
    }

    const T& back() const{
        if(this->_size >= this->_capacity){
            throw std::overflow_error("Queue has no back element");
        }

        size_t index = (this->_enqueue == 0) ? (this->_capacity - 1) : (this->_enqueue - 1);
        return this->array[index]; 
    }

    size_t capacity() const{
        return this->_capacity;
    }

    size_t size() const{
        return this->_size;
    }

    bool full() const{
        return this->_size >= this->_capacity;
    }

    bool empty() const{
        return this->_size == 0;
    }
};

int main(void){
    CQueue<int, 5> queue;

    for(int i = 0; i < 5; ++i){
        queue.enqueue(i);
    }

    queue.front() = 69;

    for(int i = 0; i < 10; ++i){
        std::cout << queue.dequeue() << '\n';
        queue.enqueue(i);
    }

    for(int i = 0; i < 5; ++i){
        std::cout << queue.dequeue() << '\n';
    }

    return 0;
}

