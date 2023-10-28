#ifndef H_TOKEN
#define H_TOKEN

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

enum TokenType {
    NUMBER, 
    
    SINE,
    COSINE,
    TANGENT,
    COTANGENT,

    ADDITION,
    MULTIPLICATION,
    SUBTRACTION,
    DIVISION,
    EXPONENTIATION,

    LEFT_PARENTHESIS,
    LEFT_CURLY_PARENTHESIS,
    RIGHT_PARENTHESIS,
    RIGHT_CURLY_PARENTHESIS,

    NULLVAL
};

class Token {
    public:
        static std::map<std::string, TokenType> tokenSpec;

        Token(TokenType type, std::string value) {
            this->type = type;
            this->value = value;
        }

        TokenType type;
        std::string value;
};

#endif