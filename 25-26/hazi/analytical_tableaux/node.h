#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace logic {

enum class Operator : char32_t {
    NOT = U'¬',   // !, ¬, ~
    AND = U'∧',   // &, ∧
    OR = U'∨',    // |, ∨
    IFF = U'→',   // →, ⊃, ⇒
    IMPLY = U'↔', // ↔, ⇔
    NIL = 0,
};

enum class Literal : unsigned char {
    A = 'A',
    B = 'B',
    C = 'C',
    D = 'D',
    E = 'E',
    F = 'F',
    G = 'G',
    H = 'H',
    I = 'I',
    J = 'J',
    K = 'K',
    L = 'L',
    M = 'M',
    N = 'N',
    O = 'O',
    P = 'P',
    Q = 'Q',
    R = 'R',
    S = 'S',
    T = 'T',
    U = 'U',
    V = 'V',
    W = 'W',
    X = 'X',
    Y = 'Y',
    Z = 'Z',
    NIL = 0,
};

struct Node {
    std::variant<Operator, Literal> value;
    std::vector<std::shared_ptr<Node>> children;

    Node(Literal lit) : value(lit) {
    }

    Node(Operator expr) : value(expr) {
    }

    Node(const std::variant<Operator, Literal> &value) : value(value) {
    }

    Node(const Node &other) : value(other.value) {
        for(const auto &child : other.children) {
            children.push_back(child->clone());
        }
    }

    bool is_leaf() const {
        return std::holds_alternative<Literal>(value) && children.empty();
    }

    bool is_operator() const {
        return std::holds_alternative<Operator>(value);
    }

    bool is_literal() const {
        return std::holds_alternative<Literal>(value);
    }

    Operator get_operator() const {
        return std::get<Operator>(value);
    }

    Literal get_literal() const {
        return std::get<Literal>(value);
    }

    std::shared_ptr<Node> clone() const {
        return std::make_shared<Node>(*this);
    }
};

namespace {
const std::unordered_map<char32_t, Operator> char32_expr_map = {
    // clang-format off
    {U'!', Operator::NOT},
    {U'¬', Operator::NOT}, 
    {U'~', Operator::NOT},   
    {U'&', Operator::AND},
    {U'∧', Operator::AND}, 
    {U'|', Operator::OR},  
    {U'∨', Operator::OR},    
    {U'→', Operator::IFF},
    {U'⊃', Operator::IFF}, 
    {U'⇒', Operator::IFF}, 
    {U'↔', Operator::IMPLY}, 
    {U'⇔', Operator::IMPLY},
    // clang-format on
};

const std::unordered_map<unsigned char, Literal> char_lit_map = {
    {'A', Literal::A}, {'B', Literal::B}, {'C', Literal::C}, {'D', Literal::D}, {'E', Literal::E},
    {'F', Literal::F}, {'G', Literal::G}, {'H', Literal::H}, {'I', Literal::I}, {'J', Literal::J},
    {'K', Literal::K}, {'L', Literal::L}, {'M', Literal::M}, {'N', Literal::N}, {'O', Literal::O},
    {'P', Literal::P}, {'Q', Literal::Q}, {'R', Literal::R}, {'S', Literal::S}, {'T', Literal::T},
    {'U', Literal::U}, {'V', Literal::V}, {'W', Literal::W}, {'X', Literal::X}, {'Y', Literal::Y},
    {'Z', Literal::Z},
};
} // namespace

static Operator Char32ToOperator(char32_t chr) {
    if(!char32_expr_map.count(chr))
        return Operator::NIL;
    return char32_expr_map.at(chr);
}

static char32_t OperatorToChar32(Operator exprt) {
    return static_cast<char32_t>(exprt);
}

static Literal CharToLiteral(unsigned char chr) {
    if(!char_lit_map.count(chr))
        return Literal::NIL;
    return char_lit_map.at(chr);
}

static unsigned char LiteralToChar(Literal lit) {
    return static_cast<unsigned char>(lit);
}

static std::shared_ptr<Node> ExpressionToNNF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node;

    Operator op = node->get_operator();

    switch(op) {
        case Operator::NOT: {
            auto child = node->children[0];
            if(child->is_operator()) {
                Operator child_op = child->get_operator();

                switch(child_op) {
                    // ¬¬A => A
                    case Operator::NOT: {
                        return ExpressionToNNF(child->children[0]);
                    }
                    // ¬(A ∧ B) => (¬A ∨ ¬B)
                    case Operator::AND: {
                        auto not_a = std::make_shared<Node>(Operator::NOT);
                        not_a->children.push_back(child->children[0]);
                        auto not_b = std::make_shared<Node>(Operator::NOT);
                        not_b->children.push_back(child->children[1]);
                        auto or_node = std::make_shared<Node>(Operator::OR);
                        or_node->children.push_back(ExpressionToNNF(not_a));
                        or_node->children.push_back(ExpressionToNNF(not_b));
                        return or_node;
                    }
                    // ¬(A v B) => (¬A ∧ ¬B)
                    case Operator::OR: {
                        auto not_a = std::make_shared<Node>(Operator::NOT);
                        not_a->children.push_back(child->children[0]);
                        auto not_b = std::make_shared<Node>(Operator::NOT);
                        not_b->children.push_back(child->children[1]);
                        auto and_node = std::make_shared<Node>(Operator::AND);
                        and_node->children.push_back(ExpressionToNNF(not_a));
                        and_node->children.push_back(ExpressionToNNF(not_b));
                        return and_node;
                    }
                    // ¬(A → B) => (A ∧ ¬B)
                    case Operator::IMPLY: {
                        auto not_b = std::make_shared<Node>(Operator::NOT);
                        not_b->children.push_back(child->children[1]);
                        auto and_node = std::make_shared<Node>(Operator::AND);
                        and_node->children.push_back(ExpressionToNNF(child->children[0]));
                        and_node->children.push_back(ExpressionToNNF(not_b));
                        return and_node;
                    }
                    // ¬(A ↔ B) => (A ∧ ¬B) ∨ (¬A ∧ B)
                    case Operator::IFF: {
                        auto not_a = std::make_shared<Node>(Operator::NOT);
                        not_a->children.push_back(child->children[0]);
                        auto not_b = std::make_shared<Node>(Operator::NOT);
                        not_b->children.push_back(child->children[1]);

                        auto left_and = std::make_shared<Node>(Operator::AND);
                        left_and->children.push_back(ExpressionToNNF(child->children[0]));
                        left_and->children.push_back(ExpressionToNNF(not_b));

                        auto right_and = std::make_shared<Node>(Operator::AND);
                        right_and->children.push_back(ExpressionToNNF(not_a));
                        right_and->children.push_back(ExpressionToNNF(child->children[1]));

                        auto or_node = std::make_shared<Node>(Operator::OR);
                        or_node->children.push_back(left_and);
                        or_node->children.push_back(right_and);
                        return or_node;
                    }
                    default:
                        return node;
                }
            }
            return node;
        }
        // (A ∧ B)
        case Operator::AND:
        // (A ∨ B)
        case Operator::OR: {
            auto new_node = std::make_shared<Node>(op);
            for(auto &child : node->children) {
                new_node->children.push_back(ExpressionToNNF(child));
            }
            return new_node;
        }
        // A → B => ¬A ∨ B
        case Operator::IMPLY: {
            auto not_a = std::make_shared<Node>(Operator::NOT);
            not_a->children.push_back(node->children[0]);
            auto or_node = std::make_shared<Node>(Operator::OR);
            or_node->children.push_back(ExpressionToNNF(not_a));
            or_node->children.push_back(ExpressionToNNF(node->children[1]));
            return or_node;
        }
        // A ↔ B => (A ∧ B) ∨ (¬A ∧ ¬B)
        case Operator::IFF: {
            auto not_a = std::make_shared<Node>(Operator::NOT);
            not_a->children.push_back(node->children[0]);
            auto not_b = std::make_shared<Node>(Operator::NOT);
            not_b->children.push_back(node->children[1]);

            auto left_and = std::make_shared<Node>(Operator::AND);
            left_and->children.push_back(ExpressionToNNF(node->children[0]));
            left_and->children.push_back(ExpressionToNNF(node->children[1]));

            auto right_and = std::make_shared<Node>(Operator::AND);
            right_and->children.push_back(ExpressionToNNF(not_a));
            right_and->children.push_back(ExpressionToNNF(not_b));

            auto or_node = std::make_shared<Node>(Operator::OR);
            or_node->children.push_back(left_and);
            or_node->children.push_back(right_and);
            return or_node;
        }
        default:
            return node;
    }
}

static bool is_negated_literal(std::shared_ptr<Node> node) {
    return node->is_operator() && node->get_operator() == Operator::NOT &&
           node->children[0]->is_literal();
}

static Literal GetLiteralFromNegated(std::shared_ptr<Node> node) {
    return node->children[0]->get_literal();
}

} // namespace logic
