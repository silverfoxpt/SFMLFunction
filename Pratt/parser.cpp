#include "parser.h"

void Parser::Initialize(sf::RenderWindow* window, Lexer* lex) {
    this->window = window;
    this->lex = lex;
}

void Parser::Update(sf::Event event) {
}

void Parser::Visualize(sf::Event event) {

}

void Parser::LateUpdate() {

}

void Parser::Reset() {

}

int Parser::GetPrecedence(Token token) {
    if (this->precedence.find(token.value) == this->precedence.end()) {
        return 0;
    }

    return this->precedence[token.value];
}

float Parser::Evaluate(std::string input) {
    this->lex->InitiateInput(input);
    float output = this->Expression(0);
    return output;
}

float Parser::Expression(int curPrecedence) {
    float lhs = this->PrefixHandler();

    while (curPrecedence < this->GetPrecedence(this->lex->GetCurrentToken())) {
        lhs = this->InfixHandler(lhs, this->lex->GetCurrentToken().type);
    }

    return lhs;
}

float Parser::InfixHandler(float lhs, TokenType type) {
    Token curToken = this->lex->GetCurrentToken();
    this->lex->Eat(type);

    int newPrec = this->GetPrecedence(curToken);
    if (type == TokenType::ADDITION) {
        return lhs + this->Expression(newPrec);
    } else if (type == TokenType::MULTIPLICATION) {
        return lhs * this->Expression(newPrec);
    } else if (type == TokenType::SUBTRACTION) {
        return lhs - this->Expression(newPrec);
    } else if (type == TokenType::DIVISION) {
        return lhs / this->Expression(newPrec);
    } else if (type == TokenType::EXPONENTIATION) {
        return std::pow(lhs, this->Expression(newPrec - 1)); 
        //power rule follows right hand first
        //for example, 2^3^5 should be evaluated as 2^(3^5), not (2^3)^5 like addition or multiplication
    }

    throw std::invalid_argument("Undefined operators/number detected");
}

float Parser::PrefixHandler() {
    Token curToken = this->lex->GetCurrentToken();

    if (curToken.type == TokenType::SUBTRACTION) {
        curToken.value = "unary";
        this->lex->Eat(TokenType::SUBTRACTION);

        return -this->Expression(this->GetPrecedence(curToken));
    }

    if (curToken.type == TokenType::ADDITION) {
        curToken.value = "unary";
        this->lex->Eat(TokenType::ADDITION);

        return +this->Expression(this->GetPrecedence(curToken));
    }
    
    if (curToken.type == TokenType::LEFT_PARENTHESIS) {
        this->lex->Eat(TokenType::LEFT_PARENTHESIS);
        float exp = this->Expression(0);
        this->lex->Eat(TokenType::RIGHT_PARENTHESIS);

        return exp;
    }

    this->lex->Eat(TokenType::NUMBER);
    return std::stof(curToken.value);
}