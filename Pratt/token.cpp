#include "token.h"

std::map<std::string, TokenType> Token::tokenSpec = {
    {"+", TokenType::ADDITION},
    {"*", TokenType::MULTIPLICATION},
    {"-", TokenType::SUBTRACTION},
    {"/", TokenType::DIVISION},
    {"^", TokenType::EXPONENTIATION},

    {"(", TokenType::LEFT_PARENTHESIS},
    {")", TokenType::RIGHT_PARENTHESIS}
};