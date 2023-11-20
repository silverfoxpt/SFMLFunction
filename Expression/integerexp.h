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

namespace exp {
    class Integer: public Expression<int> {
    public:
        Integer(int value) : Expression<int>(ExpressionType::Integer, value) {
            
        }
    };
}

#endif