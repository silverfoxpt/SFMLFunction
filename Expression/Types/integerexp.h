#ifndef H_INTEGEREXP
#define H_INTEGEREXP

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
#include "fracexp.h"

class IntegerExpression: public Expression{
    public:
        IntegerExpression(int value) : Expression(ExpressionType::Integer, value) {
            
        }

        //implicit conversion to fraction expression
        operator FractionExpression() const {
            return FractionExpression({std::get<int>(this->value), 1});
        }

        std::string GetDescription() override {
            return "<IntegerExpression " + std::to_string(std::get<int>(this->GetValue())) + " >";
        }
};

#endif