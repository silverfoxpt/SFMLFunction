#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "Reuseable/gameManager.h"
#include "Reuseable/randomsfml.h"
#include "Reuseable/math.h"
#include "Reuseable/gameobjectmanager.h"

#include "Reuseable/stringhelp.h"
#include "RPN/rpn.h"

#include "Pratt/parser.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Function");
sf::Clock deltaTime;

RPN myRpn;
Lexer lex;
Parser parser;

//static vars
float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

void InitializeTest() {
    
}

void PostInitializeTest() {
    std::string infix = "5+2*3";
    std::cout << infix << " = " << parser.Evaluate(infix) << '\n';

    infix = "5+2+3";
    std::cout << infix << " = " << parser.Evaluate(infix) << '\n';
}

void Initialize() {
    InitializeTest();

    myRpn.Initialize(&window);
    lex.Initialize(&window);
    parser.Initialize(&window, &lex);

    PostInitializeTest();
}

void Update(sf::Event event) {
    myRpn.Update(event);
}

void Visualize(sf::Event event) {
    myRpn.Visualize(event);
}

void LateUpdate() {
    myRpn.LateUpdate();
}

void Reset() {
    myRpn.Reset();
}

int main()
{
    Initialize();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        //run
        Update(event);
        Visualize(event);
        LateUpdate();

        window.display();
    }

    return 0;
}