//
// Expression Tree implementation for the 2025-11-12 homework
// C++17 compatible
//
#include <iostream>
#include <string>

#include "expr_tree.h"
#include "node.h"

static size_t _spart_global_counter = 0;
#define spart(...) test_part(++_spart_global_counter, [&]() { __VA_ARGS__ })

// Wrapper class
class Formula {
  private:
    mutable logic::AnalyticalTableaux tableaux_;

    void push_(const std::string &expr) {
        tableaux_.push(logic::parse_expression(expr));
    }

    void push_(std::shared_ptr<logic::Node> node) {
        tableaux_.push(node);
    }

  public:
    Formula(const std::string &expr) {
        push_(expr);
    }

    Formula(std::shared_ptr<logic::Node> node) {
        push_(node);
    }

    bool Kielégíthető() const {
        return tableaux_.is_satisfiable();
    }

    void Igazságérték(const std::string &expr) {
        if(tableaux_.get_formulas().size() < 1) {
            throw std::runtime_error("Üres formulához nem adhatsz igazságértéket.");
        }
        push_(expr);
    }

    Formula NemÉs() const {
        Formula formula = logic::ExpressionToANDF(tableaux_.get_formulas()[0]);
        return formula;
    }
};

// For safer running
template <typename Function>
void test_part(size_t count, Function func) {
    try {
        func();
        std::cout << count << ". Makulátlan futás\n\n";

    } catch(...) {
        std::cout << count << ". Hibás futás\n\n";
    }
}

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
        // std::cout << "Formulas are consistent (possible)\n";
    }
    else {
        // std::cout << "Formulas are inconsistent (impossible)\n";
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
    spart( //
        Formula formula("!(A & B) | C");
        //
    );

    // 2.
    spart( //
        Formula formula("!A > B");

        formula.Igazságérték("A"); formula.Igazságérték("!B");
        // Or
        formula.Igazságérték("A & !B");

        std::cout << "2. ¬A → B Kielégíthető-e, ha A és ¬B: "
                  << (formula.Kielégíthető() ? "Igen\n" : "Nem\n");
        //
    );

    return 0;
}
