#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

enum class ExprType : char32_t {
    NOT = U'¬', // !, ¬, ~
    AND = U'∧', // &, ∧
    OR,         // |, ∨
    IFF,        // →, ⊃, ⇒
    IMPLY,      // ↔, ⇔
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
    Z = 'Z'
};

struct Node {
    std::variant<ExprType, Literal> value;
    std::vector<std::shared_ptr<ExprType>> children;

    Node(Literal lit) : value(lit) {
    }

    Node(ExprType expr) : value(expr) {
    }
};

static std::unordered_map<char32_t, ExprType> char32_expr_map;
static std::unordered_map<ExprType, char32_t> expr_char32_map;
static std::unordered_map<unsigned char, Literal> char_lit_map;

ExprType CharToExprType(std)
