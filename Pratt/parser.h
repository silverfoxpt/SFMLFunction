#ifndef H_PARSER
#define H_PARSER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "../Reuseable/templateclass.h"
#include "../Reuseable/stringhelp.h"
#include "lexer.h"

struct Func {
    bool matched;
    float value;
};

class Parser: Monobehaviour<sf::RenderWindow*, Lexer*> {
    public:
        sf::RenderWindow* window;
        Lexer* lex;

        void Initialize(sf::RenderWindow* window, Lexer* lex) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        float Evaluate(std::string input);
        float Expression(int curPrecedence);
        float PrefixHandler();

        Func TrigPrefixHandler();
        float CurlyParenthesisHandler();

        float InfixHandler(float lhs, TokenType type);

        int GetPrecedence(Token token);

    private:
        std::map<std::string, int> precedence = {
            {"+", 2},
            {"-", 2},
            {"*", 3},
            {"/", 3},
            {"unary", 4},
            {"^", 5}
        };
        
};

#endif