#include "token.h"

std::map<std::string, TokenType> Token::tokenSpec = {
    {"+", TokenType::ADDITION},
    {"*", TokenType::MULTIPLICATION},
};