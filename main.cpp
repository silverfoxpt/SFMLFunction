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

#include "Text/textelement.h"
#include "Text/textelementmanager.h"
#include "Text/displaygroup.h"

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

TextElementManager textElementManager;

//static vars
float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(800, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

//test vars
sf::Font font;

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

//NOTE: REMEMBER TO DEACTIVATE THIS TEST
void ASTParserTest() {
    std::string infix = "5-(2+3)*8^2-\\sin{3+8}";
    ASTNode* root = astParser.Parse(infix);
    //astParser.Debug(root, 0);
}

void TextTest() {
    auto t1 = textElementManager.CreateDisplayText("2");
    auto t2 = textElementManager.CreateDisplayText("+");
    auto t3 = textElementManager.CreateDisplayText("3");

    auto group1 = DisplayGroup({t1}, Token(TokenType::NULLVAL, "0")); 
    auto group2 = DisplayGroup({t2}, Token(TokenType::NULLVAL, "0"));
    auto group3 = DisplayGroup({t3}, Token(TokenType::NULLVAL, "0"));

    group2.moveX(group1.GetTotalWidth());
    group3.moveX(group2.GetTotalWidth());

    group3.Merge(group2);
    group3.Merge(group1);

    group3.Scale(2);
}

void InitializeTest() {
    //DO NOT PUT SHIT IN HERE UNLESS YOU'RE SURE THEY RUN BEFORE INITIALIZATION HAPPENS
}

void PostInitializeTest() {
    EvaluateParserTest();
    ASTParserTest();
    TextTest();
}

void Initialize() {
    if (!font.loadFromFile("./font/MathJax_Main-Regular.otf"))
    {
        std::cerr << "Can't load font!";
    }

    InitializeTest();

    myRpn.Initialize(&window);
    lex.Initialize(&window);
    parser.Initialize(&window, &lex);

    astLex.Initialize(&window);
    astParser.Initialize(&window, &astLex);

    textElementManager.Initialize(&window, font);
    PostInitializeTest();
}

void Update(sf::Event event) {
    myRpn.Update(event);
    textElementManager.Update(event);
}

void Visualize(sf::Event event) {
    myRpn.Visualize(event);
    textElementManager.Visualize(event);
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