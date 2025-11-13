#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "node.h"

namespace logic {

class AnalyticalTableaux {
  private:
    std::vector<std::shared_ptr<Node>> formulas_;
    std::unordered_set<Literal> positive_literals_;
    std::unordered_set<Literal> negative_literals_;

    bool backtrack_tableaux(const std::vector<std::shared_ptr<Node>> &rem_formulas) {
        if(rem_formulas.empty()) {
            for(auto pos_lit : positive_literals_) {
                if(negative_literals_.find(pos_lit) != negative_literals_.end()) {
                    return false;
                }
            }
            return true;
        }

        auto current = rem_formulas[0];
        std::vector<std::shared_ptr<Node>> rest(rem_formulas.begin() + 1, rem_formulas.end());

        if(current->is_literal()) {
            positive_literals_.insert(current->get_literal());
            bool result = backtrack_tableaux(rest);
            positive_literals_.erase(current->get_literal());
            return result;
        }
        else if(is_negated_literal(current)) {
            Literal lit = GetLiteralFromNegated(current);
            negative_literals_.insert(lit);
            bool result = backtrack_tableaux(rest);
            negative_literals_.erase(lit);
            return result;
        }
        else if(current->is_operator()) {
            Operator op = current->get_operator();

            switch(op) {
                case Operator::AND: {
                    std::vector<std::shared_ptr<Node>> new_rest = rest;
                    new_rest.push_back(current->children[0]);
                    new_rest.push_back(current->children[1]);
                    return backtrack_tableaux(new_rest);
                }
                case Operator::OR: {
                    std::vector<std::shared_ptr<Node>> left_branch = rest;
                    left_branch.push_back(current->children[0]);

                    std::vector<std::shared_ptr<Node>> right_branch = rest;
                    right_branch.push_back(current->children[1]);

                    return backtrack_tableaux(left_branch) || backtrack_tableaux(right_branch);
                }
                default:
                    return false;
            }
        }
        return false;
    }

  public:
    AnalyticalTableaux(const std::vector<std::shared_ptr<Node>> &formulas) : formulas_(formulas) {
    }

    bool is_satisfiable() {
        std::vector<std::shared_ptr<Node>> nnf_formulas;
        for(auto &formula : formulas_) {
            nnf_formulas.push_back(ExpressionToNNF(formula));
        }
        return backtrack_tableaux(nnf_formulas);
    }
};

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

static bool is_consistent(const std::vector<std::shared_ptr<Node>> &formulas) {
    AnalyticalTableaux tableaux(formulas);
    return tableaux.is_satisfiable();
}

static bool is_contradiction(const std::vector<std::shared_ptr<Node>> &formulas) {
    return !is_consistent(formulas);
}

} // namespace logic
