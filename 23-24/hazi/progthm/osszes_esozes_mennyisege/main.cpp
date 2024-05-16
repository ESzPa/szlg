#include <iostream>

int main(){
    int days;
    std::cin >> days;

    int sum = 0;
    int _;
    for(int i = 0; i < days; ++i){
        std::cin >> _;
        sum += _;
    }
    std::cout << sum;
    return 0;
}
