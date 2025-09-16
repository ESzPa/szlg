#include <vector>

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

int main(void){

    return 0;
}
