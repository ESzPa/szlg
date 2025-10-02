#pragma once

#include "constants.h"

std::unordered_map<char, uint8_t> ops_precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'%', 2},
    {'^', 3},
    {'!', 4}
};

std::string infix_postfix_parse(const std::string& infix_string){
    std::stack<char> stack;
    std::string output = "";

    for(const char& c : infix_string){
        if(binary_ops_list.find(c) != std::string::npos){
            while(!stack.empty() && stack.top() != '(' 
                    && ops_precedence[c] <= ops_precedence[stack.top()]){
                output += stack.top(); stack.pop();
            }
            stack.push(c);
        }
        else if(unary_ops_list.find(c) != std::string::npos){
            while(!stack.empty() && stack.top() != '(' 
                    && ops_precedence[c] < ops_precedence[stack.top()]){
                output += stack.top(); stack.pop();
            }
            stack.push(c);
        }
        else if(operands_list.find(c) != std::string::npos){
            output += c;
        }
        else if(c == '('){
            stack.push(c);
        }
        else if(c == ')'){
            while(!stack.empty() && stack.top() != '('){
                output += stack.top(); stack.pop();
            }
            stack.pop();
        }
        else{
            throw std::invalid_argument("invalid character: " + std::to_string(c));
        }
    }

    while(!stack.empty()){
        if(stack.top() == '('){
            throw std::invalid_argument("invalid parentheses");
        }
        output += stack.top(); stack.pop();
    }

    return output;
}


