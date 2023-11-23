#ifndef H_PRODEXP
#define H_PRODEXP

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

class ProductExpression : public Expression{
    public:
        ProductExpression(std::string value) : Expression(ExpressionType::ProdOp, value) {
            
        }

        std::string GetDescription() override {
            return "<Product Expression * >";
        }
};


#endif