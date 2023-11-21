#ifndef H_QUOTEXP
#define H_QUOTEXP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "expression.h"

class QuotientExpression : public Expression{
    public:
        QuotientExpression(std::string value) : Expression(ExpressionType::QuotOp, value) {
            
        }
};


#endif