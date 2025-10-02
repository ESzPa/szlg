#include "infix.h"


int main(void){
    std::cout << infix_postfix_parse("((3+3)*(6*9)!)") << '\n';
    
    return 0;
}
