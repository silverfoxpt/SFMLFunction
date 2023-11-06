#ifndef H_DISPLAYELEMENT
#define H_DISPLAYELEMENT

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

class DisplayElement {
    public:
        virtual void SetPosition(sf::Vector2f pos) = 0;
        virtual void Move(sf::Vector2f dir) = 0;

        virtual void Draw(sf::RenderWindow* window) = 0;
        virtual void Scale(float sc) = 0;

        virtual void SetHardOrigin() = 0;

        virtual sf::Vector2f GetPosition() = 0;
        virtual float GetHeight() = 0;
        virtual float GetWidth() = 0;

        virtual float GetBottomX() = 0;
        virtual float GetBottomY() = 0;
};

#endif
