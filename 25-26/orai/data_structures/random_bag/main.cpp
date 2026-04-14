#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

template<typename T> 
class RandomBag{
private:
    std::vector<T> inner_list;

public:
    void Push(T item){
        inner_list.push_back(item);
    }

    T Peek(){
        if(inner_list.empty()) return T();

        size_t index = rand() % inner_list.size();
        
        std::swap(inner_list[index], inner_list.back());

        return inner_list.back(); 
    }

    T Pop(){
        if(inner_list.empty()) return T();

        size_t index = rand() % inner_list.size();
        
        std::swap(inner_list[index], inner_list.back());

        T _ = inner_list.back();
        inner_list.pop_back();

        return _; 
    }

    bool Empty(){
        return inner_list.empty();
    }

    void Clear(){
        inner_list.clear();
    }

    size_t Size(){
        return inner_list.size();
    }
};

int main(void){
    srand(time(NULL));

    RandomBag<int> baggybag;
    for(int i = 0; i < 1000000; ++i){
        baggybag.Push(rand() % 1024);
    }

    /*
    for(int i = 0; i < 30; ++i){
        for(int j = 0; j < 15; ++j){
            std::cout << baggybag.Pop() << '\t';
        }
        std::cout << '\n';
    }
    */

    std::cout << baggybag.Size() << '\n';

    return 0;
}
