#include <iostream>
#include <string>
#include <cstdint>
#include <stack>
#include <cmath>
#include <functional>
#include <unordered_map>

uint64_t calc_factorial(uint64_t a){
    if(a < 2) return 1;
    
    uint64_t result = 2;
    for(uint64_t i = 3; i <= a; ++i){
        result *= i;
    }

    return result;
}

uint64_t calc_power(uint64_t a, uint64_t b){
    uint64_t result = 1;
    while(b){
        if(b & 1) result *= a;
        a *= a;
        b >>= 1;
    }
    return result;
}

constexpr std::string_view binary_ops_list = "+-*^%";
constexpr std::string_view unary_ops_list = "!";
constexpr std::string_view operands_list = "1234567890";

std::unordered_map<char, std::function<uint64_t(uint64_t, uint64_t)>> binary_ops_map = {
    {'+', [](uint64_t a, uint64_t b){ return a + b; }},
    {'-', [](uint64_t a, uint64_t b){ return a - b; }},
    {'*', [](uint64_t a, uint64_t b){ return a * b; }},
    {'^', [](uint64_t a, uint64_t b){ return std::pow(a, b); }},
    {'%', [](uint64_t a, uint64_t b){ return a % b; }}
};

std::unordered_map<char, std::function<uint64_t(uint64_t)>> unary_ops_map = {
    {'!', [](uint64_t a){ return calc_factorial(a); }}
};

uint64_t postfix_calculate(std::string postfix_string){
    std::stack<uint64_t> operands;
    for(const char& c : postfix_string){
        if(binary_ops_list.find(c) != std::string_view::npos){
            uint64_t b = operands.top(); operands.pop();
            uint64_t a = operands.top(); operands.pop();
            operands.push(binary_ops_map[c](a, b));
        }
        else if(unary_ops_list.find(c) != std::string_view::npos){
            uint64_t a = operands.top(); operands.pop();
            operands.push(unary_ops_map[c](a));
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
