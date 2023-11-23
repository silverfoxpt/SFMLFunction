#include "astconvert.h"

void ASTConverter::Initialize(sf::RenderWindow* window, ASTParser* parser, ExpressionManager* manager) {
    this->window = window;
    this->mainParser = parser;
    this->expressionManager = manager;
}

void ASTConverter::Update(sf::Event event) {
}

void ASTConverter::Visualize(sf::Event event) {

}

void ASTConverter::LateUpdate() {

}

void ASTConverter::Reset() {

}

std::weak_ptr<Expression> ASTConverter::ConvertASTToExpressionTree(ASTNode* root) {
    if (root->type == TokenType::NUMBER) {
        std::shared_ptr<IntegerExpression> tmp = std::make_shared<IntegerExpression>(IntegerExpression(std::stoi(root->value)));
        std::shared_ptr<Expression> newNumber = std::static_pointer_cast<Expression>(tmp);
        return this->expressionManager->AddNewControlledComponent(newNumber);
    }
    
    if (root->type == TokenType::SYMBOL) {
        std::shared_ptr<SymbolExpression> tmp = std::make_shared<SymbolExpression>(SymbolExpression(root->value));
        std::shared_ptr<Expression> newSymbol = std::static_pointer_cast<Expression>(tmp);
        return this->expressionManager->AddNewControlledComponent(newSymbol);
    } 

    if (root->type == TokenType::ADDITION) {
        if (root->value == "unary") { //deal with unary operator (same type as sum)
            auto first = this->ConvertASTToExpressionTree(root->children[0]); // +x = x
            return first;
        }

        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        SumExpression exp("+");
        exp.AddSubexpression({first, second});

        auto tmp = std::make_shared<SumExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::SUBTRACTION) {
        if (root->value == "unary") { //deal with - unary operator (same type as difference)
            auto first = this->expressionManager->AddNewControlledComponent(
                std::static_pointer_cast<Expression>(std::make_shared<IntegerExpression>(IntegerExpression(-1)))
            );
            auto second = this->ConvertASTToExpressionTree(root->children[0]);

            ProductExpression prod("*");
            prod.AddSubexpression({first, second}); // -x = (-1) * x

            return this->expressionManager->AddNewControlledComponent(
                std::static_pointer_cast<Expression>(std::make_shared<ProductExpression>(prod))
            );
        }

        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        auto third = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<IntegerExpression>(IntegerExpression(-1)))
        );

        ProductExpression prod("*");
        prod.AddSubexpression({third, second}); // -x = (-1) * x

        auto fourth = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<ProductExpression>(prod))
        );

        SumExpression exp("+");
        exp.AddSubexpression({first, fourth}); // a - b = a + (-1) * b

        auto tmp = std::make_shared<SumExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::MULTIPLICATION) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        ProductExpression exp("*");
        exp.AddSubexpression({first, second});

        auto tmp = std::make_shared<ProductExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::DIVISION) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        PowerExpression powy("^");
        auto third = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<IntegerExpression>(IntegerExpression(-1)))
        );
        powy.AddSubexpression({second, third});

        auto fourth = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<PowerExpression>(powy))
        );

        ProductExpression exp("*");
        exp.AddSubexpression({first, fourth}); // a/b = a * (b^(-1))

        auto tmp = std::make_shared<ProductExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::EXPONENTIATION) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        PowerExpression exp("^");
        exp.AddSubexpression({first, second});

        auto tmp = std::make_shared<PowerExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    //functions down here
    if (Token::isFunction(root->type)) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);

        FunctionExpression exp(root->value, this->convertTypeFunction[root->type]);
        exp.AddSubexpression(first);

        return this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<FunctionExpression>(exp))
        );
    }

    return std::weak_ptr<Expression>();
}