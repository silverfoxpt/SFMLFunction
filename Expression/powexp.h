#ifndef H_POWEXP
#define H_POWEXP

#include "expression.h"

class PowerExpression: public Expression{
    public:
        PowerExpression(std::string value) : Expression(ExpressionType::PowOp, value) {
            
        }
};

#endif