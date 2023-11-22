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
#include "Pratt/expvisual.h"

#include "Text/textelement.h"
#include "Text/textelementmanager.h"
#include "Text/recmanager.h"
#include "Text/displaygroup.h"

#include "Expression/expressionmanager.h"
#include "Expression/expression.h"

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
RectangleElementManager rectangleElementManager;
ExpressionVisual expressionVisual;

ExpressionManager expressionManager;

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
    std::string infix = "0";
    ASTNode* root = astParser.Parse(infix);
    //astParser.Debug(root, 0);
}

void TextTest() {
    std::string infix = "\\sin{a^2+5}*(5-c*(2/3))/(2*x*y-2)*y/2";
    //std::string infix = "(5-(2+3)*8^2-\\sin{3+8})^(\\sin{2/3+1})*10^(-99+\\tan{23-6})";
    //std::string infix = "2*(-3)";
    //std::string infix = "(2/3)^(3/2)";

    /*astParser.Reset();
    rectangleElementManager.Reset();
    textElementManager.Reset();

    ASTNode* root = astParser.Parse(infix);

    expressionVisual.Reset();
    auto finalDisplay = expressionVisual.Evaluate(root);

    astParser.Debug(root, 0);*/
} 

void ExpressionTest() {
    IntegerExpression a(5);
    FractionExpression b = a;

    auto tester = expressionManager.AddNewControlledComponent(std::make_shared<Expression>(b));
    if (auto pt = tester.lock()) {
        auto value = pt.get()->GetValue();
        std::pair<int, int> val = std::get<std::pair<int, int>>(value);

        std::cout << val.first << " " << val.second << '\n';
    }
}

void PreInitializeTest() {
    //DO NOT PUT SHIT IN HERE UNLESS YOU'RE SURE THEY RUN BEFORE INITIALIZATION HAPPENS
}

void PostInitializeTest() {
    EvaluateParserTest();
    ASTParserTest();
    TextTest();

    ExpressionTest();
}

void Initialize() {
    if (!font.loadFromFile("./font/MathJax_Main-Regular.otf"))
    {
        std::cerr << "Can't load font!";
    }

    PreInitializeTest();
    rectangleElementManager.Initialize(&window);
    textElementManager.Initialize(&window, font);

    myRpn.Initialize(&window);
    lex.Initialize(&window);
    parser.Initialize(&window, &lex);

    astLex.Initialize(&window);
    astParser.Initialize(&window, &astLex);
    expressionVisual.Initialize(&window, &astParser, &textElementManager, &rectangleElementManager);
    expressionManager.Initialize(&window);

    PostInitializeTest();
}

void Update(sf::Event event) {
    myRpn.Update(event);
    textElementManager.Update(event);
    rectangleElementManager.Update(event);
}

void Visualize(sf::Event event) {
    myRpn.Visualize(event);
    textElementManager.Visualize(event);
    rectangleElementManager.Visualize(event);
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