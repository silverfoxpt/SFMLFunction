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

class ExpressionVisual: Monobehaviour<sf::RenderWindow*, ASTParser*> {
    public:
        sf::RenderWindow* window;
        ASTParser* parser;

        void Initialize(sf::RenderWindow* window, ASTParser* parser) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        
};

#endif