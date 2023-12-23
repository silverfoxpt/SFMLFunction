#ifndef H_EXPVISUAL
#define H_EXPVISUAL

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "astparser.h"
#include "../Text/displaygroup.h"
#include "../Text/textelementmanager.h"
#include "../Text/recmanager.h"

class ExpressionVisual: Monobehaviour<sf::RenderWindow*, ASTParser*, TextElementManager*, RectangleElementManager*> {
    public:
        sf::RenderWindow* window;
        ASTParser* parser;
        TextElementManager* textManager;
        RectangleElementManager* recManager;

        void Initialize(sf::RenderWindow* window, ASTParser* parser, TextElementManager* textManager, 
            RectangleElementManager* recManager) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        DisplayGroup Evaluate(ASTNode* root);

        //variables
        int horizontalBuffer = 5;
        int exponentHorizontalBuffer = 2;
        int verticalBuffer = 8;
        int lineWidthBuffer = 20;
        float exponentScale = 0.9f;
        float parenthesisScale = 1.2f;

    private:
        DisplayGroup GetDisplayGroupFromText(std::string text, Token prevToken);
        DisplayGroup GetDisplayGroupFromRec(int width, Token prevToken);

        DisplayGroup MergeGroupToRight(DisplayGroup first, DisplayGroup second);
        DisplayGroup MergeGroupToBottom(DisplayGroup first, DisplayGroup second, bool boundAnchorToFirst);
        DisplayGroup ParenthesizeGroup(DisplayGroup group);
        
};

#endif