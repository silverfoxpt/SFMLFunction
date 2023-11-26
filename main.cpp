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
#include "Expression/astconvert.h"
#include "Expression/simplifyrational.h"

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
ASTConverter astConverter;
SimplifyRational simplifyRational;

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
    //passed
    /*IntegerExpression a(5);
    FractionExpression b = a;

    auto tester = expressionManager.AddNewControlledComponent(std::make_shared<Expression>(b));
    if (auto pt = tester.lock()) {
        auto value = pt.get()->GetValue();
        std::pair<int, int> val = std::get<std::pair<int, int>>(value);

        std::cout << val.first << " " << val.second << '\n';
    }*/

    //passed
    /*std::string infix = "a*b*c+x*y*z-b*c*(a+b+c*a*b+a)";
    astParser.Reset();
    ASTNode* root = astParser.Parse(infix);

    auto rootExp = astConverter.ConvertASTToExpressionTree(root);
    if (auto pt = rootExp.lock()) {
        ASTConverter::Debug(rootExp, 0);
    }

    std::cout << "\n" << "Flatten:\n";
    astConverter.FlattenProductExpressionTree(rootExp);
    astConverter.FlattenSumExpressionTree(rootExp);
    if (auto pt = rootExp.lock()) {
        ASTConverter::Debug(rootExp, 0);
    }*/
}

void RandomValueTest() {
    //passed
    /*FractionExpression a({20, 0});
    auto pt = expressionManager.AddConvertibleExpression(a);
    auto ret = simplifyRational.SimplifyRationalNumber(pt);

    if (auto newPt = ret.lock()) {
        if (newPt.get()->GetType() == ExpressionType::FracOp) {
            std::pair<int, int> val = std::get<std::pair<int, int>>(newPt.get()->GetValue());
            std::cout << "TESTVAL: " << val.first << " " << val.second << '\n';
        } else if (newPt.get()->GetType() == ExpressionType::Undefined) {
            std::cout << "TESTVAL: Undefined" << '\n';
        } else {
            int val = std::get<int>(newPt.get()->GetValue());
            std::cout << "TESTVAL: " << val << '\n';
        }
    }*/

    std::string infix = "1/2+2/3+3/4";
    astParser.Reset();
    ASTNode* root = astParser.Parse(infix);

    auto rootExp = astConverter.ConvertASTToExpressionTree(root);
    if (auto pt = rootExp.lock()) {
        ASTConverter::Debug(rootExp, 0);
    }

    std::cout << "\n" << "Flatten:\n";
    astConverter.FlattenProductExpressionTree(rootExp);
    astConverter.FlattenSumExpressionTree(rootExp);
    if (auto pt = rootExp.lock()) {
        ASTConverter::Debug(rootExp, 0);
    }

    auto val = simplifyRational.SimpilfyRNE(rootExp);
    if (auto newPt = val.lock()) {
        if (newPt.get()->GetType() == ExpressionType::FracOp) {
            std::pair<int, int> val = std::get<std::pair<int, int>>(newPt.get()->GetValue());
            std::cout << "TESTVAL: " << val.first << " " << val.second << '\n';
        } else if (newPt.get()->GetType() == ExpressionType::Undefined) {
            std::cout << "TESTVAL: Undefined" << '\n';
        } else {
            int val = std::get<int>(newPt.get()->GetValue());
            std::cout << "TESTVAL: " << val << '\n';
        }
    }

    //comparison test - passed
    //auto t1 = expressionManager.AddConvertibleExpression(FractionExpression({1, 2}));
    //std::cout << "TEST COMP: " << simplifyRational.Compare(t1, 0.5) << '\n';
}

void PreInitializeTest() {
    //DO NOT PUT SHIT IN HERE UNLESS YOU'RE SURE THEY RUN BEFORE INITIALIZATION HAPPENS
}

void PostInitializeTest() {
    EvaluateParserTest();
    ASTParserTest();
    TextTest();

    ExpressionTest();
    RandomValueTest();
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
    simplifyRational.Initialize(&window, &expressionManager);

    astConverter.Initialize(&window, &astParser, &expressionManager);

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