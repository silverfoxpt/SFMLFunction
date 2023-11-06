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

class TextElementManager: Monobehaviour<sf::RenderWindow*>, Manager<TextElement>{
    public:
        sf::RenderWindow* window;

        TextElementManager() : Manager() {}

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

    private:
        
};

#endif