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
    if (root->children.size() == 0) { //leaf node
        if (root->type == TokenType::NUMBER) {
            std::shared_ptr<Expression> newNumber = std::make_shared<Expression>(IntegerExpression(std::stoi(root->value)));
            this->expressionManager->AddNewControlledComponent(newNumber);
        }
        else if (root->type == TokenType::SYMBOL) {
            //std::shared_ptr<Expression> newSymbol = std::make_shared<Expression>(IntegerExpression(std::stoi(root->value)));
            //this->expressionManager->AddNewControlledComponent(newNumber);
        }
    }
}