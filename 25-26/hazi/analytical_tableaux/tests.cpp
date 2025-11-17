#define CATCH_CONFIG_MAIN

#include "catch2/catch_amalgamated.hpp"
#include "expr_tree.h"
#include "node.h"

// !! AI WRITTEN TESTS
// !! THEY **MIGHT** BE WRONG

TEST_CASE("Basic literal parsing", "[parser]") {
    SECTION("Single uppercase letter") {
        auto expr = logic::parse_expression("A");
        REQUIRE(expr->is_literal());
        REQUIRE(expr->get_literal() == logic::Literal::A);
    }

    SECTION("All uppercase letters") {
        for(char c = 'A'; c <= 'Z'; ++c) {
            std::string expr_str(1, c);
            auto expr = logic::parse_expression(expr_str);
            REQUIRE(expr->is_literal());
        }
    }
}

TEST_CASE("Basic operator parsing", "[parser]") {
    SECTION("AND operator") {
        auto expr = logic::parse_expression("A & B");
        REQUIRE(expr->is_operator());
        REQUIRE(expr->get_operator() == logic::Operator::AND);
        REQUIRE(expr->children.size() == 2);
        REQUIRE(expr->children[0]->get_literal() == logic::Literal::A);
        REQUIRE(expr->children[1]->get_literal() == logic::Literal::B);
    }

    SECTION("OR operator") {
        auto expr = logic::parse_expression("A | B");
        REQUIRE(expr->get_operator() == logic::Operator::OR);
    }

    SECTION("NOT operator") {
        auto expr = logic::parse_expression("!A");
        REQUIRE(expr->get_operator() == logic::Operator::NOT);
        REQUIRE(expr->children[0]->get_literal() == logic::Literal::A);
    }

    SECTION("Implication operator") {
        auto expr = logic::parse_expression("A > B");
        REQUIRE(expr->get_operator() == logic::Operator::IMPLY);
    }

    SECTION("Biconditional operator") {
        auto expr = logic::parse_expression("A = B");
        REQUIRE(expr->get_operator() == logic::Operator::IFF);
    }
}

TEST_CASE("Complex expressions", "[parser]") {
    SECTION("AND with NOT") {
        auto expr = logic::parse_expression("A & !B");
        REQUIRE(expr->get_operator() == logic::Operator::AND);
        REQUIRE(expr->children[0]->get_literal() == logic::Literal::A);
        REQUIRE(expr->children[1]->get_operator() == logic::Operator::NOT);
    }

    SECTION("Double negation") {
        auto expr = logic::parse_expression("!!A");
        REQUIRE(expr->get_operator() == logic::Operator::NOT);
        REQUIRE(expr->children[0]->get_operator() == logic::Operator::NOT);
    }

    SECTION("Parentheses grouping") {
        auto expr = logic::parse_expression("(A | B) & C");
        REQUIRE(expr->get_operator() == logic::Operator::AND);
        REQUIRE(expr->children[0]->get_operator() == logic::Operator::OR);
    }

    SECTION("Nested parentheses") {
        auto expr = logic::parse_expression("((A | B) & C)");
        REQUIRE(expr->get_operator() == logic::Operator::AND);
        REQUIRE(expr->children[0]->get_operator() == logic::Operator::OR);
    }
}

TEST_CASE("Operator precedence", "[parser]") {
    SECTION("AND has higher precedence than OR") {
        auto expr = logic::parse_expression("A & B | C");
        REQUIRE(expr->get_operator() == logic::Operator::OR); // (A & B) | C
        REQUIRE(expr->children[0]->get_operator() == logic::Operator::AND);
    }

    SECTION("NOT has highest precedence") {
        auto expr = logic::parse_expression("!A & B");
        REQUIRE(expr->get_operator() == logic::Operator::AND); // (!A) & B
        REQUIRE(expr->children[0]->get_operator() == logic::Operator::NOT);
    }
}

TEST_CASE("NNF conversion", "[nnf]") {
    SECTION("Double negation elimination") {
        auto expr = logic::parse_expression("!!A");
        auto nnf = logic::ExpressionToNNF(expr);
        REQUIRE(nnf->is_literal());
        REQUIRE(nnf->get_literal() == logic::Literal::A);
    }

    SECTION("De Morgan - AND to OR") {
        auto expr = logic::parse_expression("!(A & B)");
        auto nnf = logic::ExpressionToNNF(expr);
        REQUIRE(nnf->get_operator() == logic::Operator::OR);
        REQUIRE(nnf->children[0]->get_operator() == logic::Operator::NOT);
        REQUIRE(nnf->children[1]->get_operator() == logic::Operator::NOT);
    }

    SECTION("De Morgan - OR to AND") {
        auto expr = logic::parse_expression("!(A | B)");
        auto nnf = logic::ExpressionToNNF(expr);
        REQUIRE(nnf->get_operator() == logic::Operator::AND);
        REQUIRE(nnf->children[0]->get_operator() == logic::Operator::NOT);
        REQUIRE(nnf->children[1]->get_operator() == logic::Operator::NOT);
    }

    SECTION("Implication elimination") {
        auto expr = logic::parse_expression("A > B");
        auto nnf = logic::ExpressionToNNF(expr);
        REQUIRE(nnf->get_operator() == logic::Operator::OR);
        REQUIRE(nnf->children[0]->get_operator() == logic::Operator::NOT);
    }

    SECTION("Biconditional elimination") {
        auto expr = logic::parse_expression("A = B");
        auto nnf = logic::ExpressionToNNF(expr);
        REQUIRE(nnf->get_operator() == logic::Operator::OR);
    }
}

TEST_CASE("Error handling", "[errors]") {
    SECTION("Empty expression throws") {
        REQUIRE_THROWS_AS(logic::parse_expression(""), std::runtime_error);
    }

    SECTION("Missing operand after operator throws") {
        REQUIRE_THROWS_AS(logic::parse_expression("A &"), std::runtime_error);
    }

    SECTION("Missing operand before operator throws") {
        REQUIRE_THROWS_AS(logic::parse_expression("& B"), std::runtime_error);
    }

    SECTION("Unmatched opening parenthesis throws") {
        REQUIRE_THROWS_AS(logic::parse_expression("(A & B"), std::runtime_error);
    }

    SECTION("Unmatched closing parenthesis throws") {
        REQUIRE_THROWS_AS(logic::parse_expression("A & B)"), std::runtime_error);
    }

    SECTION("Invalid character throws") {
        REQUIRE_THROWS_AS(logic::parse_expression("A @ B"), std::runtime_error);
    }

    SECTION("Lowercase literal throws") {
        REQUIRE_THROWS_AS(logic::parse_expression("a & B"), std::runtime_error);
    }

    SECTION("Multiple operators throws") {
        REQUIRE_THROWS_AS(logic::parse_expression("A & & B"), std::runtime_error);
    }
}

TEST_CASE("Expression tree structure", "[tree]") {
    SECTION("Literal has no children") {
        auto expr = logic::parse_expression("A");
        REQUIRE(expr->children.empty());
    }

    SECTION("NOT has one child") {
        auto expr = logic::parse_expression("!A");
        REQUIRE(expr->children.size() == 1);
    }

    SECTION("Binary operators have two children") {
        auto expr = logic::parse_expression("A & B");
        REQUIRE(expr->children.size() == 2);
    }

    SECTION("Complex tree structure") {
        auto expr = logic::parse_expression("!(A & B) | C");
        REQUIRE(expr->get_operator() == logic::Operator::OR);
        REQUIRE(expr->children.size() == 2);
        REQUIRE(expr->children[0]->get_operator() == logic::Operator::NOT);
        REQUIRE(expr->children[1]->is_literal());
    }
}

TEST_CASE("Consistency checking - Basic cases", "[consistency]") {
    SECTION("Single literal is always consistent") {
        auto expr = logic::parse_expression("A");
        logic::formula_list formulas = {expr};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("A and !A are inconsistent") {
        auto expr1 = logic::parse_expression("A");
        auto expr2 = logic::parse_expression("!A");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == false);
    }

    SECTION("A and B are consistent") {
        auto expr1 = logic::parse_expression("A");
        auto expr2 = logic::parse_expression("B");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("A & !A is inconsistent") {
        auto expr = logic::parse_expression("A & !A");
        logic::formula_list formulas = {expr};
        REQUIRE(logic::is_consistent(formulas) == false);
    }
}

TEST_CASE("Consistency checking - Complex formulas", "[consistency]") {
    SECTION("De Morgan example 1") {
        auto expr1 = logic::parse_expression("!(A & B) | C");
        auto expr2 = logic::parse_expression("(!A | !B) | C");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("De Morgan example 2") {
        auto expr1 = logic::parse_expression("!(A | B)");
        auto expr2 = logic::parse_expression("!A & !B");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Biconditional with negation") {
        auto expr1 = logic::parse_expression("(A = B) & (!C | D)");
        auto expr2 = logic::parse_expression("A = B");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Complex equivalence") {
        auto expr1 = logic::parse_expression("!(A | B) = !(A & !B)");
        logic::formula_list formulas = {expr1};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Implication chain") {
        auto expr1 = logic::parse_expression("(A & B) > (C | !D)");
        auto expr2 = logic::parse_expression("A & B");
        auto expr3 = logic::parse_expression("!C & D");
        logic::formula_list formulas = {expr1, expr2, expr3};
        REQUIRE(logic::is_consistent(formulas) == false);
    }
}

TEST_CASE("Consistency checking - Real world scenarios", "[consistency]") {
    SECTION("Simple puzzle 1") {
        auto rain_wet = logic::parse_expression("R > W");
        auto raining = logic::parse_expression("R");
        auto ground_wet = logic::parse_expression("W");
        logic::formula_list formulas = {rain_wet, raining, ground_wet};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Simple puzzle 2") {
        auto rain_wet = logic::parse_expression("R > W");
        auto raining = logic::parse_expression("R");
        auto ground_not_wet = logic::parse_expression("!W");
        logic::formula_list formulas = {rain_wet, raining, ground_not_wet};
        REQUIRE(logic::is_consistent(formulas) == false);
    }

    SECTION("Logic puzzle") {
        auto either = logic::parse_expression("J | M");
        auto not_john = logic::parse_expression("!J");
        auto mary_smart = logic::parse_expression("M");
        logic::formula_list formulas = {either, not_john, mary_smart};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Contradictory puzzle") {
        auto both = logic::parse_expression("J & M");
        auto not_john = logic::parse_expression("!J");
        auto mary_smart = logic::parse_expression("M");
        logic::formula_list formulas = {both, not_john, mary_smart};
        REQUIRE(logic::is_consistent(formulas) == false);
    }
}

TEST_CASE("Consistency checking - Edge cases", "[consistency]") {
    SECTION("Empty formula list") {
        logic::formula_list formulas = {};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Tautology is always consistent") {
        auto tautology = logic::parse_expression("A | !A");
        logic::formula_list formulas = {tautology};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Contradiction is never consistent") {
        auto contradiction = logic::parse_expression("A & !A");
        logic::formula_list formulas = {contradiction};
        REQUIRE(logic::is_consistent(formulas) == false);
    }

    SECTION("Multiple independent variables") {
        auto expr1 = logic::parse_expression("A & B & C & D & E");
        auto expr2 = logic::parse_expression("!A | !B | !C | !D | !E");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == false);
    }
}

TEST_CASE("Consistency checking - NNF transformations", "[consistency]") {
    SECTION("Double negation doesn't affect consistency") {
        auto expr1 = logic::parse_expression("A");
        auto expr2 = logic::parse_expression("!!A");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("De Morgan consistency") {
        auto expr1 = logic::parse_expression("!(A & B)");
        auto expr2 = logic::parse_expression("!A | !B");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Implication transformation consistency") {
        auto expr1 = logic::parse_expression("A > B");
        auto expr2 = logic::parse_expression("!A | B");
        logic::formula_list formulas = {expr1, expr2};
        REQUIRE(logic::is_consistent(formulas) == true);
    }
}

TEST_CASE("Consistency checking - Your specific examples", "[consistency]") {
    SECTION("Your example 1") {
        auto expr1 = logic::parse_expression("!(A & B) | C");
        auto expr2 = logic::parse_expression("(A = B) & (!C | D)");
        logic::formula_list formulas = {expr1, expr2};
        bool result = logic::is_consistent(formulas);
        REQUIRE(result == true);
    }

    SECTION("Your example 2") {
        auto expr1 = logic::parse_expression("!(A | B) = !(A & !B)");
        logic::formula_list formulas = {expr1};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Your example 3") {
        auto expr1 = logic::parse_expression("(A & B) > (C | !D)");
        auto expr2 = logic::parse_expression("A & B");
        auto expr3 = logic::parse_expression("!C & D");
        logic::formula_list formulas = {expr1, expr2, expr3};
        REQUIRE(logic::is_consistent(formulas) == false);
    }
}

TEST_CASE("Consistency checking - Performance stress tests", "[consistency]") {
    SECTION("Many independent variables") {
        logic::formula_list formulas;

        formulas.push_back(logic::parse_expression("A"));
        formulas.push_back(logic::parse_expression("B"));
        formulas.push_back(logic::parse_expression("C"));
        formulas.push_back(logic::parse_expression("D"));
        formulas.push_back(logic::parse_expression("E"));

        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Large conjunction") {
        auto large_and = logic::parse_expression("A & B & C & D & E & F & G & H");
        logic::formula_list formulas = {large_and};
        REQUIRE(logic::is_consistent(formulas) == true);
    }

    SECTION("Complex nested expressions") {
        auto complex = logic::parse_expression("((A > B) & (B > C)) > (A > C)");
        logic::formula_list formulas = {complex};
        REQUIRE(logic::is_consistent(formulas) == true);
    }
}
