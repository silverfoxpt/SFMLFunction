#ifndef H_EXPRESSION
#define H_EXPRESSION

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <variant>

enum ExpressionType {
    Integer,
    FracOp,

    SumOp,
    DiffOp,
    ProdOp,
    PowOp,
    QuotOp,

    FuncOp
};
using ValueVariant = std::variant<int, std::pair<int, int>, std::string>;

class Expression {
    public:
        ExpressionType type;
        ValueVariant value;
        std::vector<Expression*> subexpressions;

        Expression(ExpressionType type, ValueVariant value) {
            this->type = type;
            this->value = value;
        }

        void AddSubexpression(Expression* exp) {
            if (exp == nullptr) {
                return;
            }

            this->subexpressions.push_back(exp);
        }

        void AddSubexpression(std::vector<Expression*> exp) {
            for (auto x: exp) {
                if (x == nullptr) {continue;}
                exp.push_back(x);
            }
        }

        virtual ValueVariant GetValue() {
            return this->value;
        }

        virtual ExpressionType GetType() {
            return this->type;
        }
};

#endif