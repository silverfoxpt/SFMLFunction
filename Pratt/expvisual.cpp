#include "expvisual.h"

void ExpressionVisual::Initialize(sf::RenderWindow* window, ASTParser* parser, TextElementManager* textManager) {
    this->window = window;
    this->parser = parser;
    this->textManager = textManager;
}

void ExpressionVisual::Update(sf::Event event) {

}

void ExpressionVisual::Visualize(sf::Event event) {

}

void ExpressionVisual::LateUpdate() {

}

void ExpressionVisual::Reset() {
    this->textManager->Reset();
}

DisplayGroup ExpressionVisual::Evaluate(ASTNode* root) {
    if (root->type == TokenType::NULLVAL) {
        return DisplayGroup({}, Token(TokenType::NULLVAL, "0"));
    }

    if (root->children.size() == 0) { //leaf node, handle it
        if (root->type == TokenType::NUMBER) {
            return this->GetDisplayGroupFromText(root->value, Token(root->type, root->value));
        } 

        //not recognized
        return DisplayGroup({}, Token(TokenType::NULLVAL, "0"));
    }
}

//helper function
DisplayGroup ExpressionVisual::GetDisplayGroupFromText(std::string text, Token prevToken) {
    DisplayElement* newElement = this->textManager->CreateDisplayText(text);
    DisplayGroup newDisplayGroup({newElement}, prevToken);

    return newDisplayGroup;
}