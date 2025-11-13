//
// Expression Tree implementation for the 2025-11-12 homework
// C++17 compatible
//
#include <iostream>

#include "expr_tree.h"
#include "node.h"

int main(int argc, char **argv) {
    // Example hardcoded usage

    auto expr1 = logic::parse_expression("!(A & B) | C");
    auto expr2 = logic::parse_expression("(A = B) & (!C | D)");
    auto expr3 = logic::parse_expression("!(A | B) = !(A & !B)");
    auto expr4 = logic::parse_expression("(A & B) > (C | !D)");

    logic::formula_list formulas = {expr1, expr2};

    if(logic::is_consistent(formulas)) {
        std::cout << "Formulas are consistent (possible)\n";
    }
    else {
        std::cout << "Formulas are inconsistent (impossible)\n";
    }

    return 0;
}
