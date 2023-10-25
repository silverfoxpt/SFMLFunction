#ifndef H_LEXER
#define H_LEXER

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

#include "token.h"

class Lexer: Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        void InitiateInput(std::string input);
        void Eat(TokenType type);
        Token GetCurrentToken();

        //public vars
        std::vector<Token> tokens;
        int index = 0;

    private:
        
};

#endif