#ifndef H_TEXTELEMENTMANAGER
#define H_TEXTELEMENTMANAGER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "../Reuseable/managertemplateclass.h"
#include "../Reuseable/templateclass.h"

#include "textelement.h"
#include "displayelement.h"

class DisplayElement;

class TextElementManager: Monobehaviour<sf::RenderWindow*, sf::Font>, public Manager<TextElement>{
    public:
        sf::RenderWindow* window;
        sf::Font font;

        TextElementManager() : Manager() {}

        void Initialize(sf::RenderWindow* window, sf::Font font) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        DisplayElement* GetDisplayElement(TextElement* ele) {
            if (ele == nullptr) {return nullptr;}
            return ele;
        }

        DisplayElement* CreateDisplayText(std::string tex) {
            //upcasting immediately from TextElement to DisplayElement
            return this->AddNewControlledComponent(TextElement(tex, font));
        }

    private:
        
};

#endif