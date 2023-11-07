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

#include "displayelement.h"
#include "../Pratt/token.h"

class TextElement : public DisplayElement {
    public:
        sf::Text tex;

        TextElement() { }
        TextElement(std::string text, sf::Font &font);

        void SetPosition(sf::Vector2f pos) override;
        void Draw(sf::RenderWindow* window) override;
        void Move(sf::Vector2f dir) override;
        void Scale(float sc) override;
        void SetHardOrigin() override;
        
        sf::Vector2f GetPosition() override;
        float GetBottomX() override;
        float GetBottomY() override;
        float GetHeight() override;
        float GetWidth() override;
};

#endif