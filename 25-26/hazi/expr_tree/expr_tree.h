#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

enum class ExprType : char32_t {
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
    std::variant<ExprType, Literal> value;
    std::vector<std::shared_ptr<ExprType>> children;

    Node(Literal lit) : value(lit) {
    }

    Node(ExprType expr) : value(expr) {
    }
};

namespace {
const std::unordered_map<char32_t, ExprType> char32_expr_map = {
    // clang-format off
    {U'!', ExprType::NOT},
    {U'¬', ExprType::NOT}, 
    {U'~', ExprType::NOT},   
    {U'&', ExprType::AND},
    {U'∧', ExprType::AND}, 
    {U'|', ExprType::OR},  
    {U'∨', ExprType::OR},    
    {U'→', ExprType::IFF},
    {U'⊃', ExprType::IFF}, 
    {U'⇒', ExprType::IFF}, 
    {U'↔', ExprType::IMPLY}, 
    {U'⇔', ExprType::IMPLY},
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

static ExprType Char32ToExprType(char32_t chr) {
    if(!char32_expr_map.count(chr))
        return ExprType::NIL;
    return char32_expr_map.at(chr);
}

static char32_t ExprTypeToChar32(ExprType exprt) {
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
