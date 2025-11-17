#pragma once

#include <cstdint>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

namespace logic {

enum class Operator : unsigned char {
    NOT = '!',   // !, ~
    AND = '&',   // &
    OR = '|',    // |
    IFF = '>',   // >
    IMPLY = '=', // =
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
const std::unordered_set<Operator> unary_operators_map = {Operator::NOT};

const std::unordered_set<Operator> binary_operators_map = {Operator::AND, Operator::OR, Operator::IFF,
                                                           Operator::IMPLY};

const std::unordered_map<unsigned char, Operator> char_expr_map = {
    // clang-format off
    {'!', Operator::NOT},
    //{U'¬', Operator::NOT}, 
    {'~', Operator::NOT},   
    {'&', Operator::AND},
    //{U'∧', Operator::AND}, 
    {'|', Operator::OR},  
    //{U'∨', Operator::OR},    
    //{U'→', Operator::IFF},
    //{U'⊃', Operator::IFF}, 
    //{U'⇒', Operator::IFF}, 
    {'>', Operator::IFF},
    {'=', Operator::IMPLY},
    //{U'↔', Operator::IMPLY}, 
    //{U'⇔', Operator::IMPLY},
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

const std::unordered_map<Operator, uint8_t> presedence_map = {
    // clang-format off
    {Operator::NOT, 4},
    {Operator::AND, 3},
    {Operator::OR, 2},
    {Operator::IMPLY, 1},
    {Operator::IFF, 1},
    {Operator::NIL, 0},
    // clang-format on
};

static bool has_higher_presedence(Operator op1, Operator op2) {
    return presedence_map.at(op1) > presedence_map.at(op2);
}
} // namespace

static Operator CharToOperator(unsigned char chr) {
    if(!char_expr_map.count(chr))
        return Operator::NIL;
    return char_expr_map.at(chr);
}

static unsigned char OperatorToChar(Operator exprt) {
    return static_cast<unsigned char>(exprt);
}

static Literal CharToLiteral(unsigned char chr) {
    if(!char_lit_map.count(chr))
        return Literal::NIL;
    return char_lit_map.at(chr);
}

static unsigned char LiteralToChar(Literal lit) {
    return static_cast<unsigned char>(lit);
}

static bool is_negated_literal(std::shared_ptr<Node> node) {
    return node->is_operator() && node->get_operator() == Operator::NOT &&
           node->children[0]->is_literal();
}

static Literal GetLiteralFromNegated(std::shared_ptr<Node> node) {
    return node->children[0]->get_literal();
}

static std::shared_ptr<Node> create_literal(Literal lit) {
    return std::make_shared<Node>(lit);
}

static std::shared_ptr<Node> create_not(std::shared_ptr<Node> child) {
    auto node = std::make_shared<Node>(Operator::NOT);
    node->children.push_back(child);
    return node;
}

static std::shared_ptr<Node> create_and(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::AND);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

static std::shared_ptr<Node> create_or(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::OR);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

static std::shared_ptr<Node> create_imply(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::IMPLY);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

static std::shared_ptr<Node> create_iff(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::IFF);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

namespace {
static void apply_operator(unsigned char op_char, std::stack<std::shared_ptr<Node>> &output_stack) {
    Operator op = CharToOperator(op_char);

    switch(op) {
        case Operator::NOT: {
            if(output_stack.empty())
                throw std::runtime_error("Insufficient operands for operation NOT (expected one)");
            auto operand = output_stack.top();
            output_stack.pop();
            output_stack.push(create_not(operand));
            break;
        }
        case Operator::AND:
        case Operator::OR:
        case Operator::IMPLY:
        case Operator::IFF: {
            if(output_stack.size() < 2)
                throw std::runtime_error("Insufficient operands for binary operator (expected two)");
            auto right = output_stack.top();
            output_stack.pop();
            auto left = output_stack.top();
            output_stack.pop();

            switch(op) {
                case Operator::AND:
                    output_stack.push(create_and(left, right));
                    break;
                case Operator::OR:
                    output_stack.push(create_or(left, right));
                    break;
                case Operator::IMPLY:
                    output_stack.push(create_imply(left, right));
                    break;
                case Operator::IFF:
                    output_stack.push(create_iff(left, right));
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            throw std::runtime_error("Unknown operator");
    }
}
} // namespace

static std::shared_ptr<Node> parse_expression(const std::string &expr) {
    std::stack<std::shared_ptr<Node>> output_stack;
    std::stack<unsigned char> operator_stack;

    bool expect_operand = true;
    size_t pos = 0;
    while(pos < expr.size()) {
        unsigned char c = expr.at(pos);

        if(std::isspace(c)) {
            ++pos;
            continue;
        }

        if(expect_operand) {
            if(c == '(') {
                operator_stack.push(c);
                pos++;
                continue;
            }

            if(unary_operators_map.count(CharToOperator(c))) {
                operator_stack.push(c);
                ++pos;
                continue;
            }

            if(std::isalpha(c) && std::isupper(c)) {
                Literal lit = CharToLiteral(static_cast<unsigned char>(c));
                output_stack.push(create_literal(lit));
                expect_operand = false;
                ++pos;
                continue;
            }

            throw std::runtime_error(std::string("Expected operand, found: '") + static_cast<char>(c) +
                                     "' at position " + std::to_string(pos));
        }
        else {
            if(c == ')') {
                while(!operator_stack.empty() && operator_stack.top() != '(') {
                    apply_operator(operator_stack.top(), output_stack);
                    operator_stack.pop();
                }
                if(operator_stack.empty()) {
                    throw std::runtime_error("Mismatched parentheses");
                }
                operator_stack.pop();
                expect_operand = false;
                pos++;
                continue;
            }

            if(binary_operators_map.count(CharToOperator(c))) {
                while(!operator_stack.empty() && operator_stack.top() != '(' &&
                      has_higher_presedence(CharToOperator(operator_stack.top()), CharToOperator(c))) {
                    apply_operator(operator_stack.top(), output_stack);
                    operator_stack.pop();
                }
                operator_stack.push(c);
                expect_operand = true;
                ++pos;
                continue;
            }

            throw std::runtime_error(std::string("Invalid character: '") + static_cast<char>(c) +
                                     "' at position " + std::to_string(pos));
        }
    }

    while(!operator_stack.empty()) {
        if(operator_stack.top() == '(') {
            throw std::runtime_error("Mismatched parentheses");
        }
        apply_operator(operator_stack.top(), output_stack);
        operator_stack.pop();
    }

    if(output_stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return output_stack.top();
}

// Negation Normal Form
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

} // namespace logic
