//
// Expression Tree implementation for the 2025-11-12 homework
// C++17 compatible
//
#include <iostream>

#include "expr_tree.h"
#include "node.h"

int main(void) {

    auto expr1 = logic::parse_expression("A | B");

    auto expr2 = logic::parse_expression("A & !B");

    logic::formula_list formulas = {expr1, expr2};

    if(logic::is_consistent(formulas)) {
        std::cout << "Formulas are consistent (possible)\n";
    }
    else {
        std::cout << "Formulas are inconsistent (impossible)\n";
    }

    return 0;
}
