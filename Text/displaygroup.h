#ifndef H_DISPLAYGROUP
#define H_DISPLAYGROUP

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

class DisplayGroup {
    public:
        std::vector<DisplayElement*> elements;
        Token prevToken = {TokenType::NULLVAL, "0"};

        DisplayGroup(std::vector<DisplayElement*> elements, Token prev, int anchorHeight) {
            this->elements = elements;
            this->prevToken = prev;
            this->anchorHeight = anchorHeight;
        }

        DisplayGroup() {

        }

        int GetTotalHeight();
        int GetTotalWidth();
        int GetTopX();
        int GetTopY();
        sf::Vector2f GetTop();

        void Scale(float sc);
        void moveX(float x);    
        void moveY(float y);

        void Merge(DisplayGroup other);
        void SetPosition(sf::Vector2f pos);

        int anchorHeight = 0;
};

#endif