#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "node.h"

namespace logic {

using formula_list = std::vector<std::shared_ptr<Node>>;

class AnalyticalTableaux {
  private:
    formula_list formulas_;
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
        formula_list rest(rem_formulas.begin() + 1, rem_formulas.end());

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
                    formula_list new_rest = rest;
                    new_rest.push_back(current->children[0]);
                    new_rest.push_back(current->children[1]);
                    return backtrack_tableaux(new_rest);
                }
                case Operator::OR: {
                    formula_list left_branch = rest;
                    left_branch.push_back(current->children[0]);

                    formula_list right_branch = rest;
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
    AnalyticalTableaux() {
    }

    AnalyticalTableaux(const formula_list &formulas) : formulas_(formulas) {
    }

    void push(std::shared_ptr<Node> formula) {
        formulas_.push_back(formula);
    }

    bool is_satisfiable() {
        formula_list nnf_formulas;
        for(const auto &formula : formulas_) {
            nnf_formulas.push_back(ExpressionToNNF(formula));
        }
        return backtrack_tableaux(nnf_formulas);
    }

    formula_list get_formulas() const {
        return formulas_;
    }
};

inline bool is_consistent(const formula_list &formulas) {
    AnalyticalTableaux tableaux(formulas);
    return tableaux.is_satisfiable();
}

inline bool is_contradiction(const formula_list &formulas) {
    return !is_consistent(formulas);
}

} // namespace logic
