#ifndef H_EXPVISUAL
#define H_EXPVISUAL

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "astparser.h"
#include "../Text/displaygroup.h"
#include "../Text/textelementmanager.h"

class ExpressionVisual: Monobehaviour<sf::RenderWindow*, ASTParser*, TextElementManager*> {
    public:
        sf::RenderWindow* window;
        ASTParser* parser;
        TextElementManager* textManager;

        void Initialize(sf::RenderWindow* window, ASTParser* parser, TextElementManager* textManager) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        DisplayGroup Evaluate(ASTNode* root);

    private:
        DisplayGroup GetDisplayGroupFromText(std::string text, Token prevToken);
        
};

#endif