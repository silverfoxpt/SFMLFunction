#include "lexer.h"

void Lexer::Initialize(sf::RenderWindow* window) {
    this->window = window;

    this->tokens.clear();
    this->index = 0;
}

void Lexer::Update(sf::Event event) {

}

void Lexer::Visualize(sf::Event event) {

}

void Lexer::LateUpdate() {

}

void Lexer::Reset() {
    this->tokens.clear();
    this->index = 0;
}

Token Lexer::GetCurrentToken() {
    if (this->index >= (int) this->tokens.size()) {
        return Token(TokenType::NULLVAL, "");
    }

    return this->tokens[this->index];
}

void Lexer::Eat(TokenType type) {
    Token cur = this->GetCurrentToken();

    if (cur.type == TokenType::NULLVAL) {
        throw std::out_of_range("Invalid parse! Out of token.");
    }

    if (cur.type != type) {
        throw std::invalid_argument("Invalid parse! Expected token not found.");
    }

    this->index++;
}

void Lexer::InitiateInput(std::string input) {
    this->Reset();

    int i = 0;
    while (i < (int) input.size()) {
        //match any possible operators
        bool foundOp = false;
        for (auto it: Token::tokenSpec) {
            if (StrHelp::matchAtPos(input, i, it.first)) {
                Token operatorToken(it.second, it.first);
                this->tokens.push_back(operatorToken);

                //push index
                i += it.first.size();
                foundOp = true;
                break;
            }
        }
        if (foundOp) {continue;}

        //match any possible symbol
        if (StrHelp::isAlpha(input[i])) {
            std::string parsedSym = "";
            parsedSym += input[i]; i++;

            Token symToken(TokenType::SYMBOL, parsedSym);
            this->tokens.push_back(symToken);

            continue;
        }

        //match any integers - HASN'T BEEN IMPLEMENTED FOR REAL NUMBERS!
        if (StrHelp::isNum(input[i])) {
            std::string parsedNum = "";
            while (i < (int) input.size() && StrHelp::isNum(input[i])) {
                parsedNum += input[i];
                i++;
            }

            Token numToken(TokenType::NUMBER, parsedNum);
            this->tokens.push_back(numToken);

            continue;
        }

        //match variables - HASN'T BEEN IMPLEMENTED

        throw std::invalid_argument("Undefined operators/number detected: Lexer");
    }
}