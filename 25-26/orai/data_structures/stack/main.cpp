#include <vector>
#include <stdexcept>

template<typename T>
class DStack{
private:
    std::vector<T> _stack;

public:
    void push(T value){
        this->_stack.push_back(value);
    }

    T pop(){
        T value = this->_stack.back();
        this->_stack.pop_back();
        return value;
    }

    T& top(){
        return this->_stack.back();
    }

    bool empty(){
        return this->_stack.empty();
    }

    size_t size(){
        return this->_stack.size();
    }
};

template<typename T, size_t N>
class SStack{
private:
    T _stack[N];
    size_t _size;

public:
    SStack() : _size(0) {}

    void push(T value){
        if(this->_size >= N) std::runtime_error("Stack overflow");
        this->_stack[this->_size++] = value;
    }

    T pop(){
        if(this->_size == 0) std::runtime_error("Pop from empty stack");
        --this->_size;
    }

    T& top(){
        if(this->_size == 0) std::runtime_error("Empty stack");
        return this->_stack[this->_size-1];
    }

    bool empty(){
        return this->_stack == 0;
    }

    size_t size(){
        return this->_size;
    }
};

int main(void){

    return 0;
}
