#ifndef H_SUMEXP
#define H_SUMEXP

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "../expression.h"

class SumExpression: public Expression{
    public:
        SumExpression(std::string value) : Expression(ExpressionType::SumOp, value) {
            
        }

        std::string GetDescription() override {
            return "<SumExpression + >";
        }
};


#endif