#ifndef H_UNDEFINEDEXP
#define H_UNDEFINEDEXP

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

class UndefinedExpression: public Expression{
    public:
        UndefinedExpression() : Expression(ExpressionType::Undefined, "") {
            
        }

        std::string GetDescription() override {
            return "<UndefinedExpression>";
        }
};


#endif  