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

#include "Types/integerexp.h"
#include "Types/quotexp.h"
#include "Types/sumexp.h"
#include "Types/diffexp.h"
#include "Types/prodexp.h"
#include "Types/powexp.h"
#include "Types/funcexp.h"
#include "Types/symbolexp.h"


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
        ASTNode* ConvertExpressionTreeToAST(std::weak_ptr<Expression> root);

        std::vector<std::weak_ptr<Expression>> FlattenProductExpressionTree(std::weak_ptr<Expression> root);
        std::vector<std::weak_ptr<Expression>> FlattenSumExpressionTree(std::weak_ptr<Expression> root);

        static void Debug(std::weak_ptr<Expression> root, int level);

    private:
        std::map<TokenType, ExpressionType> convertTypeFunction = {
            {TokenType::COSINE, ExpressionType::Cosine},
            {TokenType::SINE, ExpressionType::Sine},
            {TokenType::COTANGENT, ExpressionType::Cotangent},
            {TokenType::TANGENT, ExpressionType::Tangent}
        };

        std::map<ExpressionType, TokenType> convertTypeFunctionBackward = {
            {ExpressionType::Cosine, TokenType::COSINE},
            {ExpressionType::Sine, TokenType::SINE},
            {ExpressionType::Cotangent, TokenType::COTANGENT},
            {ExpressionType::Tangent, TokenType::TANGENT}
        };
};

#endif