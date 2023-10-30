#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <cassert>

#include "Reuseable/gameManager.h"
#include "Reuseable/randomsfml.h"
#include "Reuseable/math.h"
#include "Reuseable/gameobjectmanager.h"

#include "Reuseable/stringhelp.h"
#include "Reuseable/math.h"

#include "RPN/rpn.h"

#include "Pratt/parser.h"
#include "Pratt/astparser.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(800, 800), "SFML Function");
sf::Clock deltaTime;

RPN myRpn;
Lexer lex;
Parser parser;

Lexer astLex;
ASTParser astParser;

//static vars
float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

void EvaluateParserTest() {
    std::string infix = "5+2*3";
    //std::cout << infix << " = " << parser.Evaluate(infix) << '\n';
    assert(std::abs(parser.Evaluate(infix) - 11) <= Math::FloatExponent);

    infix = "5+2+3";
    //std::cout << infix << " = " << parser.Evaluate(infix) << '\n';
    assert(std::abs(parser.Evaluate(infix) - 10) <= Math::FloatExponent);

    infix = "5/2+3*5-1";
    //std::cout << infix << " = " << parser.Evaluate(infix) << '\n';
    assert(std::abs(parser.Evaluate(infix) - 16.5) <= Math::FloatExponent);

    infix = "5^2^2-3*6";
    assert(std::abs(parser.Evaluate(infix) - 607) <= Math::FloatExponent);

    infix = "5-(2+3)*8^2";
    //std::cout << infix << " = " << parser.Evaluate(infix);
    assert(std::abs(parser.Evaluate(infix) - (-315))  <= Math::FloatExponent);

    infix = "--+-+5-2+-+1";
    assert(std::abs(parser.Evaluate(infix) - (-8))  <= Math::FloatExponent);

    infix = "-+--\\sin{\\cos{\\tan{2}}}";
    assert(std::abs(parser.Evaluate(infix) - (0.54495))  <= Math::FloatExponent);
}

void ASTParserTest() {
    //std::string infix = "5-(2+3)*8^2-\\sin{3+8}";
    //ASTNode* root = astParser.Parse(infix);
    //astParser.Debug(root, 0);
}

void InitializeTest() {
    
}

void PostInitializeTest() {
    EvaluateParserTest();
    ASTParserTest();
}

void Initialize() {
    InitializeTest();

    myRpn.Initialize(&window);
    lex.Initialize(&window);
    parser.Initialize(&window, &lex);

    astLex.Initialize(&window);
    astParser.Initialize(&window, &astLex);

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