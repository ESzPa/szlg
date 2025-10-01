#include <iostream>
#include <string>
#include <cstdint>
#include <stack>
#include <cmath>
#include <functional>
#include <unordered_map>

uint64_t postfix_factorial(uint64_t num){
    if(num < 2) return 1;
    
    uint64_t result = 2;
    for(uint64_t i = 3; i <= num; ++i){
        result *= i;
    }

    return result;
}

constexpr std::string_view operators_list = "+-*^%!";
constexpr std::string_view operands_list = "1234567890";

uint64_t postfix_calculate(std::string postfix_string){
    std::stack<uint64_t> operands;
    for(const char& c : postfix_string){
        if(operators_list.find(c) != std::string_view::npos){
            switch(c){
                case '+': {
                    uint64_t a = operands.top(); operands.pop();
                    uint64_t b = operands.top(); operands.pop();
                    operands.push(a + b);
                    break;
                }

                case '-': {
                    uint64_t a = operands.top(); operands.pop();
                    uint64_t b = operands.top(); operands.pop();
                    operands.push(a - b);
                    break;
                }
      
                case '*': {
                    uint64_t a = operands.top(); operands.pop();
                    uint64_t b = operands.top(); operands.pop();
                    operands.push(a * b);
                    break;
                }

                case '^': {
                    uint64_t a = operands.top(); operands.pop();
                    uint64_t b = operands.top(); operands.pop();
                    operands.push(std::pow(a, b)); 
                    break;
                }

                case '%': {
                    uint64_t a = operands.top(); operands.pop();
                    uint64_t b = operands.top(); operands.pop();
                    operands.push(a % b); 
                    break;
                }
                
                case '!': {
                    uint64_t a = operands.top(); operands.pop();
                    operands.push(postfix_factorial(a));
                }

                default: {
                    break;
                }
            }
        }
        else if(operands_list.find(c) != std::string_view::npos){
            operands.push(c - '0');
        }
        else{
            throw std::invalid_argument("Give a number or a character");
        }
    }

    if(operands.size() > 1){
        throw std::invalid_argument("Invalid formula");
    }

    return operands.top(); 
}

void postfix_calculator(){
    bool should_exit = false;
    do {
        std::string input;
        std::cout << "> ";
        std::cin >> input;
        should_exit = input == "exit";
        if(!should_exit){
            uint64_t result = postfix_calculate(input);
            std::cout << result << '\n';
        }
    } while(true);
}

int main(void){
    postfix_calculator();
    return 0;
}
