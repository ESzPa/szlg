//
// Expression Tree implementation for the 2025-11-12 homework
// C++17 compatible
//
#include <iostream>
#include <memory>
#include <vector>

#include "expr_tree.h"
#include "node.h"

int main(void) {
    auto A = logic::create_literal(logic::Literal::A);
    auto B = logic::create_literal(logic::Literal::B);

    // ¬A ∨ B
    auto not_A = logic::create_not(A);
    auto expr1 = logic::create_or(not_A, B);

    // A ∧ ¬B
    auto not_B = logic::create_not(B);
    auto expr2 = logic::create_and(A, not_B);

    std::vector<std::shared_ptr<logic::Node>> formulas = {expr1, expr2};

    if(logic::is_consistent(formulas)) {
        std::cout << "Formulas are consistent (possible)\n";
    }
    else {
        std::cout << "Formulas are inconsistent (impossible)\n";
    }
    return 0;
}
