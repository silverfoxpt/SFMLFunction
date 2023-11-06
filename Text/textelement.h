#ifndef H_TEXTELEMENT
#define H_TEXTELEMENT

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class TextElement {
    public:
        sf::Text tex;

        TextElement() { }

        TextElement(std::string text, sf::Font &font) {
            tex.setString(text);
            tex.setFont(font);

            tex.setFillColor(sf::Color::White);
            tex.setCharacterSize(100);
            
            //VERY IMPORTANT LINE :) 
            //Put text origin back to its true bound: https://en.sfml-dev.org/forums/index.php?topic=20284.0
            //Always put this at last
            tex.setOrigin(sf::Vector2f(tex.getGlobalBounds().left, tex.getGlobalBounds().top)); 
        }

        void SetPosition(sf::Vector2f pos) {
            tex.setPosition(pos);
        }
};

#endif