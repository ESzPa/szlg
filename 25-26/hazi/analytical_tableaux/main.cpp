//
// Expression Tree implementation for the 2025-11-12 homework
// C++17 compatible
//
#include <iostream>
#include <string>

#include "expr_tree.h"
#include "node.h"

class Formula {
  private:
    logic::AnalyticalTableaux tableaux_;

  public:
    Formula(const std::string &expr) {
        tableaux_.push(logic::parse_expression(expr));
    }
};

int main(int argc, char **argv) {
    //
    // Example usage of the formal way (divine)
    //
    auto expr1 = logic::parse_expression("!(A & B) | C");
    auto expr2 = logic::parse_expression("(A = B) & (!C | D)");
    auto expr3 = logic::parse_expression("!(A | B) = !(A & !B)");
    auto expr4 = logic::parse_expression("(A & B) > (C | !D)");

    logic::formula_list formulas = {expr1, expr2, expr3, expr4};

    if(logic::is_consistent(formulas)) {
        std::cout << "Formulas are consistent (possible)\n";
    }
    else {
        std::cout << "Formulas are inconsistent (impossible)\n";
    }

    // Also possible with a class
    logic::AnalyticalTableaux tableaux(formulas);

    tableaux.push(logic::parse_expression("A = !(B | C)"));

    if(tableaux.is_satisfiable()) {
        // Same as logic::is_consistent
    }

    //
    // Example usage of the smol pp way (mortal)
    //

    // 1.
    Formula formula("!(A & B) | C");

    return 0;
}
