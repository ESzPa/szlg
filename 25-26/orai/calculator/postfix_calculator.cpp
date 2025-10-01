#include <iostream>

#include "postfix.h"

void postfix_calculator(){
    std::string input;
    while(true){
        std::cout << "> ";
        std::cin >> input;
        if(input == "exit") break;

        uint64_t result = postfix_calculate(input);
        std::cout << result << '\n';
    }
}

int main(void){
    postfix_calculator();
    return 0;
}
