#ifndef H_RECTANGLE_ELEMENT
#define H_RECTANGLE_ELEMENT

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

class RectangleElement : public DisplayElement {
    public:
        const int originalHeight = 1;
        sf::RectangleShape shape;

        RectangleElement(int width) {
            this->shape = sf::RectangleShape(sf::Vector2f(width, originalHeight));
            this->shape.setOrigin(sf::Vector2f(0, 0));
        }

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