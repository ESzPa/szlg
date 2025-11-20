#pragma once

#include <cstdint>
#include <memory>
#include <ostream>
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
    IMPLY = '>', // >
    IFF = '=',   // =
    NIL = 0,
};

enum class Literal : unsigned char {
    // Variables
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
    // Constants
    FALSUM = '_',
    VERUM = '-',
    // Additional
    NIL = 0,
};

struct Node;

namespace {
inline std::string node_to_string(std::shared_ptr<Node> node, int parent_precedence = 0,
                                  bool is_right_child = false);
}

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

    std::string to_string() const {
        return node_to_string(std::make_shared<Node>(*this));
    }
};

namespace {
const std::unordered_set<Operator> unary_operators_map = {Operator::NOT};

const std::unordered_set<Operator> binary_operators_map = {Operator::AND, Operator::OR, Operator::IFF,
                                                           Operator::IMPLY};

const std::unordered_map<std::string, Operator> str_op_map = {
    // clang-format off
    {"!", Operator::NOT},
    {"¬", Operator::NOT}, 
    {"~", Operator::NOT},   
    {"&", Operator::AND},
    {"∧", Operator::AND}, 
    {"|", Operator::OR},  
    {"∨", Operator::OR},    
    {">", Operator::IMPLY},
    {"→", Operator::IMPLY},
    {"⊃", Operator::IMPLY}, 
    {"⇒", Operator::IMPLY},
    {"=", Operator::IFF},
    {"↔", Operator::IFF}, 
    {"⇔", Operator::IFF},
    // clang-format on
};

const std::unordered_map<Operator, std::string> op_display_map = {
    {Operator::NOT, "¬"},   {Operator::AND, "∧"}, {Operator::OR, "∨"},
    {Operator::IMPLY, "→"}, {Operator::IFF, "↔"}, {Operator::NIL, ""}};

const std::unordered_map<std::string, Literal> str_lit_map = {
    {"A", Literal::A}, {"B", Literal::B}, {"C", Literal::C}, {"D", Literal::D}, {"E", Literal::E},
    {"F", Literal::F}, {"G", Literal::G}, {"H", Literal::H}, {"I", Literal::I}, {"J", Literal::J},
    {"K", Literal::K}, {"L", Literal::L}, {"M", Literal::M}, {"N", Literal::N}, {"O", Literal::O},
    {"P", Literal::P}, {"Q", Literal::Q}, {"R", Literal::R}, {"S", Literal::S}, {"T", Literal::T},
    {"U", Literal::U}, {"V", Literal::V}, {"W", Literal::W}, {"X", Literal::X}, {"Y", Literal::Y},
    {"Z", Literal::Z},
};

const std::unordered_map<Operator, uint8_t> presedence_map = {
    // clang-format off
    {Operator::NOT, 5},
    {Operator::AND, 4},
    {Operator::OR, 3},
    {Operator::IMPLY, 2},
    {Operator::IFF, 1},
    {Operator::NIL, 0},
    // clang-format on
};

inline bool has_higher_presedence(Operator op1, Operator op2) {
    return presedence_map.at(op1) > presedence_map.at(op2);
}
} // namespace

inline Operator char_to_op(std::string chr) {
    if(!str_op_map.count(chr))
        return Operator::NIL;
    return str_op_map.at(chr);
}

inline Literal char_to_lit(std::string chr) {
    if(!str_lit_map.count(chr))
        return Literal::NIL;
    return str_lit_map.at(chr);
}

inline unsigned char LiteralToChar(Literal lit) {
    return static_cast<unsigned char>(lit);
}

inline bool is_negated_literal(std::shared_ptr<Node> node) {
    return node->is_operator() && node->get_operator() == Operator::NOT &&
           node->children[0]->is_literal();
}

inline Literal GetLiteralFromNegated(std::shared_ptr<Node> node) {
    return node->children[0]->get_literal();
}

inline std::shared_ptr<Node> create_literal(Literal lit) {
    return std::make_shared<Node>(lit);
}

inline std::shared_ptr<Node> create_not(std::shared_ptr<Node> child) {
    auto node = std::make_shared<Node>(Operator::NOT);
    node->children.push_back(child);
    return node;
}

inline std::shared_ptr<Node> create_and(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::AND);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

inline std::shared_ptr<Node> create_or(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::OR);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

inline std::shared_ptr<Node> create_imply(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::IMPLY);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

inline std::shared_ptr<Node> create_iff(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = std::make_shared<Node>(Operator::IFF);
    node->children.push_back(left);
    node->children.push_back(right);
    return node;
}

inline std::shared_ptr<Node> create_nand(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = create_and(left, right);
    return create_not(node);
}

inline std::shared_ptr<Node> create_nor(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
    auto node = create_or(left, right);
    return create_not(node);
}

namespace {
inline void apply_operator(std::string op_char, std::stack<std::shared_ptr<Node>> &output_stack) {
    Operator op = char_to_op(op_char);

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

inline std::string node_to_string(std::shared_ptr<Node> node, int parent_precedence,
                                  bool is_right_child) {
    if(node->is_literal()) {
        std::string str =
            (node->get_literal() != Literal::FALSUM && node->get_literal() != Literal::VERUM)
                ? std::string(1, LiteralToChar(node->get_literal()))
                : (node->get_literal() == Literal::FALSUM ? "⊥" : "⊤");
        return str;
    }

    Operator op = node->get_operator();
    int current_precedence = presedence_map.at(op);

    if(op == Operator::NOT) {
        return op_display_map.at(op) + node_to_string(node->children[0], current_precedence, false);
    }

    bool needs_parens = (current_precedence < parent_precedence) ||
                        (current_precedence == parent_precedence && is_right_child);

    std::string left_str = node_to_string(node->children[0], current_precedence, false);
    std::string right_str = node_to_string(node->children[1], current_precedence, true);

    std::string op_str = " " + op_display_map.at(op) + " ";
    std::string result = left_str + op_str + right_str;

    return needs_parens ? "(" + result + ")" : result;
}

size_t get_utf8_char_length(const std::string &str, size_t byte_pos) {
    if(byte_pos >= str.length())
        return 0;

    unsigned char c = str[byte_pos];
    if(c < 0x80)
        return 1;
    else if((c & 0xE0) == 0xC0)
        return 2;
    else if((c & 0xF0) == 0xE0)
        return 3;
    else if((c & 0xF8) == 0xF0)
        return 4;
    else
        return 1;
}

std::string get_utf8_char_at_byte(const std::string &str, size_t byte_pos) {
    size_t len = get_utf8_char_length(str, byte_pos);
    return str.substr(byte_pos, len);
}
} // namespace

inline std::shared_ptr<Node> parse_expression(const std::string &expr) {
    std::stack<std::shared_ptr<Node>> output_stack;
    std::stack<std::string> operator_stack;

    bool expect_operand = true;
    size_t byte_pos = 0;
    while(byte_pos < expr.size()) {
        std::string c = get_utf8_char_at_byte(expr, byte_pos);
        size_t char_len = c.length();

        if(char_len == 1 && std::isspace(c[0])) {
            byte_pos += char_len;
            continue;
        }

        if(expect_operand) {
            if(c == "(") {
                operator_stack.push(c);
                byte_pos += char_len;
                continue;
            }

            if(unary_operators_map.count(char_to_op(c))) {
                operator_stack.push(c);
                byte_pos += char_len;
                continue;
            }

            if(std::isalpha(c.at(0)) && std::isupper(c.at(0))) {
                Literal lit = char_to_lit(c);
                output_stack.push(create_literal(lit));
                expect_operand = false;
                byte_pos += char_len;
                continue;
            }

            throw std::runtime_error(std::string("Expected operand, found: '") + c + "' at position " +
                                     std::to_string(byte_pos));
        }
        else {
            if(c == ")") {
                while(!operator_stack.empty() && operator_stack.top() != "(") {
                    apply_operator(operator_stack.top(), output_stack);
                    operator_stack.pop();
                }
                if(operator_stack.empty()) {
                    throw std::runtime_error("Mismatched parentheses");
                }
                operator_stack.pop();
                expect_operand = false;
                byte_pos += char_len;
                continue;
            }

            if(binary_operators_map.count(char_to_op(c))) {
                while(!operator_stack.empty() && operator_stack.top() != "(" &&
                      has_higher_presedence(char_to_op(operator_stack.top()), char_to_op(c))) {
                    apply_operator(operator_stack.top(), output_stack);
                    operator_stack.pop();
                }
                operator_stack.push(c);
                expect_operand = true;
                byte_pos += char_len;
                continue;
            }

            throw std::runtime_error(std::string("Invalid character: '") + c + "' at position " +
                                     std::to_string(byte_pos));
        }
    }

    while(!operator_stack.empty()) {
        if(operator_stack.top() == "(") {
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
inline std::shared_ptr<Node> ExpressionToNNF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node->clone();

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
                        auto not_a = create_not(child->children[0]);
                        auto not_b = create_not(child->children[1]);
                        auto or_node = create_or(ExpressionToNNF(not_a), ExpressionToNNF(not_b));
                        return or_node;
                    }
                    // ¬(A v B) => (¬A ∧ ¬B)
                    case Operator::OR: {
                        auto not_a = create_not(child->children[0]);
                        auto not_b = create_not(child->children[1]);
                        auto and_node = create_and(ExpressionToNNF(not_a), ExpressionToNNF(not_b));
                        return and_node;
                    }
                    // ¬(A → B) => (A ∧ ¬B)
                    case Operator::IMPLY: {
                        auto not_b = create_not(child->children[1]);
                        auto and_node =
                            create_and(ExpressionToNNF(child->children[0]), ExpressionToNNF(not_b));
                        return and_node;
                    }
                    // ¬(A ↔ B) => (A ∧ ¬B) ∨ (¬A ∧ B)
                    case Operator::IFF: {
                        auto not_a = create_not(child->children[0]);
                        auto not_b = create_not(child->children[1]);

                        auto left_and =
                            create_and(ExpressionToNNF(child->children[0]), ExpressionToNNF(not_b));
                        auto right_and =
                            create_and(ExpressionToNNF(not_a), ExpressionToNNF(child->children[1]));

                        auto or_node = create_or(left_and, right_and);
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
            auto not_a = create_not(node->children[0]);
            auto or_node = create_or(ExpressionToNNF(not_a), ExpressionToNNF(node->children[1]));
            return or_node;
        }
        // A ↔ B => (A ∧ B) ∨ (¬A ∧ ¬B)
        case Operator::IFF: {
            auto not_a = create_not(node->children[0]);
            auto not_b = create_not(node->children[1]);

            auto left_and =
                create_and(ExpressionToNNF(node->children[0]), ExpressionToNNF(node->children[1]));
            auto right_and = create_and(ExpressionToNNF(not_a), ExpressionToNNF(not_b));

            auto or_node = create_or(left_and, right_and);
            return or_node;
        }
        default:
            return node;
    }
}

// Here could be added CNF and DNF

// AND Form
inline std::shared_ptr<Node> ExpressionToANDF_FromNNF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node->clone();

    Operator op = node->get_operator();

    switch(op) {
        case Operator::NOT: {
            auto child = ExpressionToANDF_FromNNF(node->children[0]);

            if(child->is_operator() && child->get_operator() == Operator::NOT) {
                return child->children[0];
            }
            return create_not(child);
        }
        case Operator::AND: {
            auto left = ExpressionToANDF_FromNNF(node->children[0]);
            auto right = ExpressionToANDF_FromNNF(node->children[1]);
            return create_and(left, right);
        }
        case Operator::OR: {
            auto left = node->children[0];
            auto right = node->children[1];

            auto not_left = create_not(left);
            auto not_right = create_not(right);
            auto and_node =
                create_and(ExpressionToANDF_FromNNF(not_left), ExpressionToANDF_FromNNF(not_right));
            return create_not(and_node);
        }
        default:
            return node->clone();
    }
}

inline std::shared_ptr<Node> ExpressionToANDF(std::shared_ptr<Node> node) {
    return ExpressionToANDF_FromNNF(ExpressionToNNF(node));
}

// OR Form
inline std::shared_ptr<Node> ExpressionToORF_FromNNF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node->clone();

    Operator op = node->get_operator();

    switch(op) {
        case Operator::NOT: {
            auto child = ExpressionToORF_FromNNF(node->children[0]);

            if(child->is_operator() && child->get_operator() == Operator::NOT) {
                return child->children[0];
            }
            return create_not(child);
        }
        case Operator::AND: {
            auto left = node->children[0];
            auto right = node->children[1];

            auto not_left = create_not(left);
            auto not_right = create_not(right);
            auto or_node =
                create_or(ExpressionToORF_FromNNF(not_left), ExpressionToORF_FromNNF(not_right));
            return create_not(or_node);
        }
        case Operator::OR: {
            auto left = ExpressionToORF_FromNNF(node->children[0]);
            auto right = ExpressionToORF_FromNNF(node->children[1]);
            return create_or(left, right);
        }
        default:
            return node->clone();
    }
}

inline std::shared_ptr<Node> ExpressionToORF(std::shared_ptr<Node> node) {
    return ExpressionToORF_FromNNF(ExpressionToNNF(node));
}

// Conditional Form
inline std::shared_ptr<Node> ExpressionToCONDF_FromNNF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node->clone();

    Operator op = node->get_operator();

    switch(op) {
        case Operator::NOT: {
            auto child = ExpressionToCONDF_FromNNF(node->children[0]);

            if(child->is_operator() && child->get_operator() == Operator::NOT) {
                return child->children[0];
            }
            return create_not(child);
        }
        case Operator::AND: {
            auto left = node->children[0];
            auto right = node->children[1];

            auto not_right = create_not(right);
            auto imply_node =
                create_imply(ExpressionToCONDF_FromNNF(left), ExpressionToCONDF_FromNNF(not_right));
            auto not_node = create_not(imply_node);
            return not_node;
        }
        case Operator::OR: {
            auto left = node->children[0];
            auto right = node->children[1];

            auto not_left = create_not(left);
            return create_imply(ExpressionToCONDF_FromNNF(not_left), ExpressionToCONDF_FromNNF(right));
        }
        default:
            return node->clone();
    }
}

inline std::shared_ptr<Node> ExpressionToCONDF(std::shared_ptr<Node> node) {
    return ExpressionToCONDF_FromNNF(ExpressionToNNF(node));
}

// NOR / Peirce Form
inline std::shared_ptr<Node> ExpressionToNORF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node->clone();

    Operator op = node->get_operator();

    switch(op) {
        case(Operator::NOT): {
            auto child = ExpressionToNORF(node->children[0]);
            return create_nor(child, child);
        }
        case(Operator::AND): {
            auto left = ExpressionToNORF(node->children[0]);
            auto right = ExpressionToNORF(node->children[1]);

            auto left_nor = create_nor(left, left);
            auto right_nor = create_nor(right, right);

            return create_nor(left_nor, right_nor);
        }
        case(Operator::OR): {
            auto left = ExpressionToNORF(node->children[0]);
            auto right = ExpressionToNORF(node->children[1]);

            auto left_nor = create_nor(left, right);
            auto right_nor = create_nor(left, right);

            return create_nor(left_nor, right_nor);
        }
        case(Operator::IMPLY): {
            auto left = ExpressionToNORF(node->children[0]);
            auto right = ExpressionToNORF(node->children[1]);

            auto right_nor = create_nor(right, right);

            return create_nor(left, right_nor);
        }
        case(Operator::IFF): {
            auto left = ExpressionToNORF(node->children[0]);
            auto right = ExpressionToNORF(node->children[1]);

            auto not_left = create_nor(left, left);
            auto not_right = create_nor(right, right);

            auto left_implies_right = create_nor(left, not_right);
            auto right_implies_left = create_nor(right, not_left);

            return create_nor(left_implies_right, right_implies_left);
        }
        default:
            return node->clone();
    }
}

inline std::shared_ptr<Node> (*ExpressionToPeirceForm)(std::shared_ptr<Node>) = ExpressionToNORF;

// NAND / Sheffer Form
inline std::shared_ptr<Node> ExpressionToNANDF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node->clone();

    Operator op = node->get_operator();

    switch(op) {
        case Operator::NOT: {
            auto child = ExpressionToNANDF(node->children[0]);
            return create_nand(child, child);
        }
        case Operator::AND: {
            auto left = ExpressionToNANDF(node->children[0]);
            auto right = ExpressionToNANDF(node->children[1]);

            auto left_nand = create_nand(left, right);
            auto right_nand = create_nand(left, right);

            return create_nand(left_nand, right_nand);
        }
        case Operator::OR: {
            auto left = ExpressionToNANDF(node->children[0]);
            auto right = ExpressionToNANDF(node->children[1]);

            auto left_nand = create_nand(left, left);
            auto right_nand = create_nand(right, right);

            return create_nand(left_nand, right_nand);
        }
        case Operator::IMPLY: {
            auto left = ExpressionToNANDF(node->children[0]);
            auto right = ExpressionToNANDF(node->children[1]);

            auto right_nand = create_nand(right, right);

            return create_nand(left, right_nand);
        }
        case Operator::IFF: {
            auto left = ExpressionToNANDF(node->children[0]);
            auto right = ExpressionToNANDF(node->children[1]);

            auto not_left = create_nand(left, left);
            auto not_right = create_nand(right, right);

            auto left_implies_right = create_nand(left, not_right);
            auto right_implies_left = create_nand(right, not_left);

            return create_nand(left_implies_right, right_implies_left);
        }
        default:
            return node->clone();
    }
}

inline std::shared_ptr<Node> (*ExpressionToShefferForm)(std::shared_ptr<Node>) = ExpressionToNANDF;

// Falsum Conditional Form
inline std::shared_ptr<Node> ExpressionToFALSCONDF(std::shared_ptr<Node> node) {
    if(node->is_literal())
        return node->clone();

    Operator op = node->get_operator();
    static auto falsum = create_literal(Literal::FALSUM);

    switch(op) {
        case Operator::NOT: {
            auto child = ExpressionToFALSCONDF(node->children[0]);
            return create_imply(child, falsum->clone());
        }
        case Operator::AND: {
            auto left = ExpressionToFALSCONDF(node->children[0]);
            auto right = ExpressionToFALSCONDF(node->children[1]);

            auto fals_right = create_imply(right, falsum->clone());
            auto left_implies_fals_right = create_imply(left, fals_right);

            return create_imply(left_implies_fals_right, falsum->clone());
        }
        case Operator::OR: {
            auto left = ExpressionToFALSCONDF(node->children[0]);
            auto right = ExpressionToFALSCONDF(node->children[1]);

            auto fals_left = create_imply(left, falsum->clone());

            return create_imply(fals_left, right);
        }
        case Operator::IMPLY: {
            auto left = ExpressionToFALSCONDF(node->children[0]);
            auto right = ExpressionToFALSCONDF(node->children[1]);

            return create_imply(left, right);
        }
        case Operator::IFF: {
            auto left = node->children[0];
            auto right = node->children[1];

            auto left_implies_right = create_imply(left, right);
            auto right_implies_left = create_imply(right, left);

            auto and_node = create_and(left_implies_right, right_implies_left);
            return ExpressionToFALSCONDF(and_node);
        }
        default:
            return node->clone();
    }
}

} // namespace logic

inline std::ostream &operator<<(std::ostream &os, const logic::Node &node) {
    return os << node.to_string();
}

inline std::ostream &operator<<(std::ostream &os, const std::shared_ptr<logic::Node> &node) {
    return os << (node ? node->to_string() : "null");
}
