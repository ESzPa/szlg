#include "infix.h"
#include "postfix.h"

void infix_calculator(){
    std::string input;
    while(true){
        std::cout << "> ";
        std::cin >> input;
        if(input == "exit") break;

        uint64_t result = postfix_calculate(infix_postfix_parse(input));
        std::cout << result << '\n';
    }
} 

int main(void){
    infix_calculator(); 
    return 0;
}
