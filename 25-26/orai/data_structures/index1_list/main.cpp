#include <iostream>
#include <vector>

template<class T> class List_Index1{
private:    
    std::vector<T> inner_list;

public:
    void Add(T item){
        inner_list.push_back(item);
    }

    T Pop(){
        T item;
        if(!inner_list.empty()){
            item = inner_list.back();
            inner_list.pop_back();
        }
        return item;
    }

   size_t Count(){
       return static_cast<size_t>(inner_list.size());
   }

   T& operator[](size_t index){
       if(index > inner_list.size()) throw std::out_of_range("Index is out of range: " + std::to_string(index));
       return inner_list[index-1];
   }

    const T& operator[](size_t index) const{
       if(index > inner_list.size()) throw std::out_of_range("Index is out of range: " + std::to_string(index));
        return inner_list[index];
    }
};


int main(void){
    List_Index1<int> list;
    
    list.Add(56);

    std::cout << list.Count() << '\n'
            << list[1] << '\n';

    return 0;
}
