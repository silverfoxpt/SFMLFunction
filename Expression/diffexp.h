#ifndef H_DIFFEXP
#define H_DIFFEXP

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

class DifferenceExpression: public Expression{
    public:
        DifferenceExpression(std::string value) : Expression(ExpressionType::DiffOp, value) {
            
        }
};


#endif