#include "token.h"

std::map<std::string, TokenType> Token::tokenSpec = {
    {"+", TokenType::ADDITION},
    {"*", TokenType::MULTIPLICATION},
    {"-", TokenType::SUBTRACTION},
    {"/", TokenType::DIVISION},
    {"^", TokenType::EXPONENTIATION},

    {"(", TokenType::LEFT_PARENTHESIS},
    {")", TokenType::RIGHT_PARENTHESIS},

    {"{", TokenType::LEFT_CURLY_PARENTHESIS},
    {"}", TokenType::RIGHT_CURLY_PARENTHESIS},

    {"\\sin", TokenType::SINE},
    {"\\cos", TokenType::COSINE},
    {"\\tan", TokenType::TANGENT},
    {"\\cot", TokenType::COTANGENT},
};