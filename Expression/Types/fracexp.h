#ifndef H_FRACEXP
#define H_FRACEXP

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

class FractionExpression: public Expression{
    public:
        FractionExpression(std::pair<int, int> value) : Expression(ExpressionType::FracOp, value) {
            
        }

        std::string GetDescription() override {
            std::pair<int, int> val = std::get<std::pair<int, int>>(this->GetValue());
            return "<FractionExpression " + std::to_string(val.first) + "/" + std::to_string(val.second) + " >"; 
        }
};


#endif