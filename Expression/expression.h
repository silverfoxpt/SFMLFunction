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

        Expression(ExpressionType type, ValueVariant value) {
            this->type = type;
            this->value = value;
        }

        virtual ValueVariant GetValue() {
            return this->value;
        }

        virtual ExpressionType GetType() {
            return this->type;
        }
};

#endif