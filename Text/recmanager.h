#ifndef H_RECMANAGER
#define H_RECMANAGER

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
#include "../Reuseable/managertemplateclass.h"
#include "rectangleelement.h"

class RectangleElementManager: Monobehaviour<sf::RenderWindow*>, Manager<RectangleElement> {
    public:
        sf::RenderWindow* window;

        RectangleElementManager() : Manager() {}

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        DisplayElement* GetDisplayElement(RectangleElement* ele) {
            if (ele == nullptr) {return nullptr;}
            return ele;
        }

        DisplayElement* CreateDisplayRectangle(int width) {
            //upcasting immediately from RectangleElement to DisplayElement
            return this->AddNewControlledComponent(RectangleElement(width));
        }

    private:
        
};

#endif