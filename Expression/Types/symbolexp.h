#ifndef H_SYMBOLEXP
#define H_SYMBOLEXP

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

class SymbolExpression: public Expression{
    public:
        SymbolExpression(std::string value) : Expression(ExpressionType::Symbol, value) {
            
        }

        std::string GetDescription() override {
            return "<SymbolExpression " + std::get<std::string>(this->GetValue()) + " >";
        }
};


#endif