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
#include <set>

enum ExpressionType {
    Symbol,
    Integer,
    FracOp,

    SumOp,
    DiffOp,
    ProdOp,
    PowOp,
    QuotOp,

    FuncOp,
    Sine,
    Cosine,
    Tangent,
    Cotangent
};
using ValueVariant = std::variant<int, std::pair<int, int>, std::string>;

class Expression {
    public:
        ExpressionType type;
        ValueVariant value;
        std::vector<std::weak_ptr<Expression>> subexpressions;

        Expression(ExpressionType type, ValueVariant value) {
            this->type = type;
            this->value = value;
        }

        void AddSubexpression(std::weak_ptr<Expression> exp) {
            if (exp.lock() == nullptr) {
                return;
            }

            this->subexpressions.push_back(exp);
        }

        void AddSubexpression(std::vector<std::weak_ptr<Expression>> exp) {
            for (auto x: exp) {
                if (x.lock() == nullptr) {continue;}
                this->subexpressions.push_back(x);
            }
        }

        virtual ValueVariant GetValue() {
            return this->value;
        }

        virtual ExpressionType GetType() {
            return this->type;
        }

        bool isFunction() {
            if (this->functionType.find(this->type) != this->functionType.end()) {
                return true;
            }
            return false;
        }

        virtual std::string GetDescription() {
            return "<GenericExpression>";
        }

    private:
        std::set<ExpressionType> functionType = {
            ExpressionType::FuncOp,
            ExpressionType::Sine,
            ExpressionType::Cosine,
            ExpressionType::Tangent,
            ExpressionType::Cotangent
        };
};

#endif