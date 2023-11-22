#ifndef H_ASTCONVERT
#define H_ASTCONVERT

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "expressionmanager.h"
#include "../Pratt/astparser.h"
#include "../Reuseable/templateclass.h"

#include "integerexp.h"
#include "quotexp.h"
#include "sumexp.h"
#include "diffexp.h"
#include "prodexp.h"
#include "powexp.h"
#include "funcexp.h"
#include "symbolexp.h"


class ASTConverter: Monobehaviour<sf::RenderWindow*, ASTParser*, ExpressionManager*> {
    public:
        sf::RenderWindow* window;
        ExpressionManager* expressionManager;
        ASTParser* mainParser;

        void Initialize(sf::RenderWindow* window, ASTParser* parser, ExpressionManager* manager) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        std::weak_ptr<Expression> ConvertASTToExpressionTree(ASTNode* root);

    private:
        
};

#endif