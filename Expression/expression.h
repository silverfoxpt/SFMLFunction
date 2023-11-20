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

namespace exp {
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

    class ExpressionProxy {

    };

    template <typename T>
    class Expression : public ExpressionProxy {
        public:
            ExpressionType type;
            T value;

            Expression(ExpressionType type, T value) {
                this->type = type;
                this->value = value;
            }

            virtual T GetValue() {
                return this->value;
            }

            virtual ExpressionType GetType() {
                return this->type;
            }
    };
};
#endif