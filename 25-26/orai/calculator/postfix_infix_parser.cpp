#include "postfix.h"

std::unordered_map<char, std::function<std::string(std::string, std::string)>> postfix_infix_binops = {
    {'+', [](std::string a, std::string b){ return "(" + a + "+" + b + ")"; }},
    {'-', [](std::string a, std::string b){ return "(" + a + "-" + b + ")"; }},
    {'*', [](std::string a, std::string b){ return "(" + a + "*" + b + ")"; }},
    {'^', [](std::string a, std::string b){ return "(" + a + "^" + b + ")"; }},
    {'%', [](std::string a, std::string b){ return "(" + a + "^" + b + ")"; }}
};

std::unordered_map<char, std::function<std::string(std::string)>> postfix_infix_unops = {
    {'!', [](std::string a){ return "(" + a + "!)"; }}
};

std::string postfix_infix_parse(const std::string& postfix_string){
    std::stack<std::string> operands;
    for(const char& c : postfix_string){
        if(binary_ops_list.find(c) != std::string_view::npos){
            if(operands.size() < 2){
                throw std::invalid_argument("invalid formula");
            }
            std::string b = operands.top(); operands.pop();
            std::string a = operands.top(); operands.pop();
            operands.push(postfix_infix_binops[c](a, b));
        }
        else if(unary_ops_list.find(c) != std::string_view::npos){
            if(operands.empty()){
                throw std::invalid_argument("invalid formula");
            }
            std::string a = operands.top(); operands.pop();
            operands.push(postfix_infix_unops[c](a));
        }
        else if(operands_list.find(c) != std::string_view::npos){
            operands.push(std::string(1, c));
        }
        else{
            throw std::invalid_argument("Give a number or a character");
        }
    }

    if(operands.size() > 1){
        throw std::invalid_argument("Invalid formula");
    }

    std::string parsed = operands.top();
    if(parsed[0] == '(') {
        parsed.erase(0, 1);
        parsed.erase(parsed.size()-1, 1);
    }

    return parsed; 
}

int main(int argc, char** argv){
    if(argc != 2){
        std::cerr << "Error: invalid use of program\n";
        std::cerr << "\tusage: " << argv[0] << " '<postfix formula>'\n";
        return 1;
    }

    std::string formula(argv[1]);

    if(formula == ""){
        std::cerr << "Error: no formula has been provided\n";
        std::cerr << "\tusage: " << argv[0] << " '<postfix formula>'\n"; 
        return 1;
    }

    std::cout << postfix_infix_parse(formula) << '\n';

    return 0;
}
