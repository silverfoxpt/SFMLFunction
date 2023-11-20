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

#include "expression.h"

class IntegerExpression: public Expression{
    public:
        IntegerExpression(int value) : Expression(ExpressionType::Integer, value) {
            
        }
};

#endif