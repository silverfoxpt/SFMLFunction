#ifndef H_FUNCEXP
#define H_FUNCEXP

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

class FunctionExpression : public Expression{
    public:
        FunctionExpression(std::string value) : Expression(ExpressionType::FuncOp, value) {
            
        }
};


#endif