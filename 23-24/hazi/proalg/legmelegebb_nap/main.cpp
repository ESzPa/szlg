#include <iostream>

int main(){
    int days;
    std::cin >> days;

    int _;
    std::cin >> _;
    int max = _;
    int index = 0;
    for(int i = 1; i < days; ++i){
        std::cin >> _;
        if(_ > max){
            max = _;
            index = i;
        }
    }
    std::cout << index+1;
    return 0;
}
