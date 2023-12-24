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
#include "Expression/sorter.h"
#include "Expression/autosimplify.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui-SFML.h"

//really early stuff initialization
Rand Randomize::rand;

//public vars
sf::RenderWindow window(sf::VideoMode(2000, 800), "SFML Function");
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
ExpressionSorter expressionSorter;
ExpressionAutoSimplify autoSimplify;

//static vars
float GameManager::windowWidth                  = window.getSize().x;
float GameManager::windowHeight                 = window.getSize().y;
float GameManager::deltaTime                    = 1/300.0;

sf::Vector2u GameManager::mainWindowSize        = sf::Vector2u(2000, 800);
sf::Vector2u GameManager::originalResolution    = sf::Vector2u(1920, 1080);

//normal vars
sf::Font font;

std::string pastInput = "";

char bufferInput[10000];
std::string input = "";

DisplayGroup originalDisplay;
DisplayGroup sanitizedDisplay;
DisplayGroup finalDisplay;

sf::Text firstText;
sf::Text firstEvaluation;
sf::Text secondText;
sf::Text thirdText;
sf::Text fourthText;

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
    //std::string infix = "0";
    //ASTNode* root = astParser.Parse(infix);
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

    //RNE - Rational Number Evaluation - value test - success
    /*std::string infix = "1/2+2/3+3/4";
    astParser.Reset();
    ASTNode* root = astParser.Parse(infix);

    auto rootExp = astConverter.ConvertASTToExpressionTree(root);
    if (auto pt = rootExp.lock()) {
        //ASTConverter::Debug(rootExp, 0);
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
    }*/

    //comparison test - passed
    //auto t1 = expressionManager.AddConvertibleExpression(FractionExpression({1, 2}));
    //std::cout << "TEST COMP: " << simplifyRational.Compare(t1, 0.5) << '\n';
}

void TermConstTest() {
    /*std::string infix = "(2+3)";
    astParser.Reset();
    ASTNode* root = astParser.Parse(infix);

    std::cout << "All:\n";
    auto rootExp = astConverter.ConvertASTToExpressionTree(root);
    astConverter.FlattenProductExpressionTree(rootExp);
    astConverter.FlattenSumExpressionTree(rootExp);

    if (auto pt = rootExp.lock()) {
        ASTConverter::Debug(rootExp, 0);
    }*/
    
    //power test - passed
    /*std::cout << "Base:\n";
    auto base = expressionSorter.Base(rootExp);
    if (auto pt = base.lock()) {
        ASTConverter::Debug(base, 0);
    }

    std::cout << "Exponent:\n";
    auto expon = expressionSorter.Exponent(rootExp);
    if (auto pt = base.lock()) {
        ASTConverter::Debug(expon, 0);
    }*/

    //product term-const test - Passed
    /*std::cout << "Const:\n";
    auto base = expressionSorter.Constant(rootExp);
    if (auto pt = base.lock()) {
        ASTConverter::Debug(base, 0);
    }

    std::cout << "Terms:\n";
    auto expon = expressionSorter.Term(rootExp);
    if (auto pt = base.lock()) {
        ASTConverter::Debug(expon, 0);
    }*/
}

void EqualizeTest() {
    //Equalize test - passed
    /*std::string infix   = "2*x^2+1/3^2*\\sin{3}";
    std::string infix2  = "2*x^2+1/3^2*\\sin{3}";

    astParser.Reset();
    ASTNode* root = astParser.Parse(infix);
    auto rootExp = astConverter.ConvertASTToExpressionTree(root);
    astConverter.FlattenProductExpressionTree(rootExp);
    astConverter.FlattenSumExpressionTree(rootExp);

    astParser.Reset();
    ASTNode* root2 = astParser.Parse(infix2);
    auto rootExp2 = astConverter.ConvertASTToExpressionTree(root2);
    astConverter.FlattenProductExpressionTree(rootExp2);
    astConverter.FlattenSumExpressionTree(rootExp2);

    std::cout << "Equal: " << expressionSorter.Equal(rootExp, rootExp2) << '\n';*/
}

//helper function, please don't mess with it too much
std::weak_ptr<Expression> infixToFlattenedExpression(std::string infix) {
    astParser.Reset();
    ASTNode* root = astParser.Parse(infix);
    auto rootExp = astConverter.ConvertASTToExpressionTree(root);
    astConverter.FlattenProductExpressionTree(rootExp);
    astConverter.FlattenSumExpressionTree(rootExp);

    return rootExp;
}

void TestOrderRelation() {
    //First test - Constant vs Constant
    auto first      = expressionManager.AddConvertibleExpression(IntegerExpression(5));
    auto second     = expressionManager.AddConvertibleExpression(FractionExpression({5, 2}));
    assert(expressionSorter.OrderRelation(first, second) == false);

    //Second test - Constant vs Any other
    auto first2     = expressionManager.AddConvertibleExpression(IntegerExpression(2));
    auto second2    = infixToFlattenedExpression("2+5");
    assert(expressionSorter.OrderRelation(first2, second2) == true);

    //Third test - Symbol vs Symbol
    auto first3     = expressionManager.AddConvertibleExpression(SymbolExpression("a"));
    auto second3    = expressionManager.AddConvertibleExpression(SymbolExpression("b"));
    assert(expressionSorter.OrderRelation(first3, second3) == true);

    //Fourth test - Symbol vs Constant
    //auto first4     = expressionManager.AddConvertibleExpression(SymbolExpression("a"));
    //auto second4    = expressionManager.AddConvertibleExpression(FractionExpression({5, 2}));
    //assert(expressionSorter.OrderRelation(first4, second4) == false);

    //Fifth test - Product vs Product (1)
    auto first5     = infixToFlattenedExpression("a*b");
    auto second5    = infixToFlattenedExpression("a*c");
    assert(expressionSorter.OrderRelation(first5, second5) == true);

    //Sixth test - Product vs Product (2)
    auto first6     = infixToFlattenedExpression("a*c*d");
    auto second6    = infixToFlattenedExpression("b*c*d");
    assert(expressionSorter.OrderRelation(first6, second6) == true);

    //Seventh test - Product vs Product (3)
    auto first7     = infixToFlattenedExpression("c*d");
    auto second7    = infixToFlattenedExpression("b*c*d");
    assert(expressionSorter.OrderRelation(first7, second7) == true);

    //Eighth test - Function vs Function
    auto first8     = infixToFlattenedExpression("\\sin{3}");
    auto second8    = infixToFlattenedExpression("\\sin{4}");
    assert(expressionSorter.OrderRelation(first8, second8) == true);

    std::cout << "Passed all Test Order Relations!\n";
}

void SorterTest() {
    //sorter test - passed
    /*
    auto exp = infixToFlattenedExpression("c+b*a+a*\\sin{b+a}+a^b+c*d*a+2*c*a*d+3*a^b");
    expressionSorter.RecursiveSortExpression(exp);

    if (auto pt = exp.lock()) {
        ASTConverter::Debug(exp, 0);
    }*/
}

void AutoSimplifyTest() {
    /*
    //std::string infix = "(2*a+b+c-4)^2*(2*a+b+c-4)+9*a*b*3+1/2*c*x*1/2*3+12*a*b*a*b^2";
    std::string infix = "a^((b^2^c +a)*(b^2+a))*a^b*a+ 3*2/9*a ^2+(2*a+b+c-4) ^2 *(2*a+b+c-4)+9*a*b*3+1/2*c*x*1/2*3+12*a*b*a*b^2";
    //std::string infix = "(a+b)^(c+d)^(e+f)";
    //std::string infix = "(a/(b/c))*((a/b)/c)";
    //std::string infix = "(a/b)*(c/d)";

    auto firstDisplay = expressionVisual.Evaluate(astParser.Parse(infix));

    auto exp = infixToFlattenedExpression(infix);
    auto simp = autoSimplify.AutoSimplify(exp);
    auto convertBack = astConverter.ConvertExpressionTreeToAST(simp);

    expressionManager.Debug();
    auto finalDisplay = expressionVisual.Evaluate(convertBack);
    finalDisplay.moveY(200);*/
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
    TermConstTest();
    EqualizeTest();

    TestOrderRelation();
    SorterTest();
    AutoSimplifyTest();
}

void MainDisplayFunction() {
    ImGui::Begin("Input");
    ImGui::InputText("Input equation", bufferInput, IM_ARRAYSIZE(bufferInput)); input = bufferInput;
    ImGui::End();

    //recalculation
    if (input != pastInput) {
        try {
            //all the nice resets
            astParser.Reset();
            textElementManager.Reset();
            rectangleElementManager.Reset();
            expressionManager.Reset();
            expressionVisual.Reset();

            auto firstDisplay = expressionVisual.Evaluate(astParser.Parse(input));

            auto exp = infixToFlattenedExpression(input);
            auto simp = autoSimplify.AutoSimplify(exp);
            auto convertBack = astConverter.ConvertExpressionTreeToAST(simp);

            expressionManager.Debug();
            auto finalDisplay = expressionVisual.Evaluate(convertBack);
            finalDisplay.moveY(200);
        } catch(std::exception e) {
            std::cerr << "Error parsing\n";
        }
    }

    //configure text

    pastInput = input;
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
    expressionSorter.Initialize(&window, &expressionManager, &simplifyRational);
    autoSimplify.Initialize(&window, &expressionManager, &simplifyRational, &expressionSorter);

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
    ImGui::SFML::Init(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaTime.restart());

        window.clear();
        
        //run
        Update(event);
        Visualize(event);
        LateUpdate();

        MainDisplayFunction();

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}