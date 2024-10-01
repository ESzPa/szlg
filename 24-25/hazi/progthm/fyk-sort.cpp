#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

void input(int &n, int &inf, int &sup){
    std::cin >> n;
    std::cin >> inf;
    std::cin >> sup;
}

int rand_between(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

std::vector<int> randomized_vector(int n, int inf, int sup){
    std::vector<int> list;
    for(int i = 0; i <= n; i++){
        list.push_back(rand_between(inf, sup));
    }
    return list;
}

void vector_print(std::vector<int> list){
    std::cout << "{ ";
    for(int i = 0; i < list.size()-2; i++){
        std::cout << list[i] << ", ";
    }
    std::cout << list[list.size()-1] << " }";
}

void swap(std::vector<int> &list, int x, int y){
    int _ = list[x];
    list[x] = list[y];
    list[y] = _;
}

void deepen(std::vector<int> &list, int i){
    for(;i > 0 && list[i-1] > list[i]; i--){
        swap(list, i-1, i);
    }
}

void vector_sort(std::vector<int> &list){
    for(int i = 0; i < list.size(); i++){
        deepen(list, i);
    }
}

void fyk(std::vector<int> &list){
    for(int i = 0; i < list.size()-1; i++){
        swap(list, i, rand_between(i+1, list.size()-1));
    }
}

int main(void)
{
    srand(time(0));
    int n, inf, sup;
    input(n, inf, sup);

    std::vector<int> list = randomized_vector(n, inf, sup);
    vector_print(list);
    std::cout << '\n';

    vector_sort(list);
    vector_print(list);
    std::cout << '\n';

    fyk(list);
    vector_print(list);
    std::cout << '\n';

    return 0;
}
