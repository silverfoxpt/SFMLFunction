#include "expvisual.h"

void ExpressionVisual::Initialize(sf::RenderWindow* window, ASTParser* parser, TextElementManager* textManager,
    RectangleElementManager* recManager) {
    this->window = window;
    this->parser = parser;
    this->textManager = textManager;
    this->recManager = recManager;
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

    if (root->children.size() == 0) { //leaf node, either number or variable, handle it
        if (root->type == TokenType::NUMBER) {
            return this->GetDisplayGroupFromText(root->value, Token(root->type, root->value));
        } 

        //not recognized
        return DisplayGroup({}, Token(TokenType::NULLVAL, "0"));
    }

    //start checking for other type of expression
    //addition - binary or unary
    if (root->type == TokenType::ADDITION || root->type == TokenType::SUBTRACTION) {
        if (root->value == "+" || root->value == "-") { //not unary
            auto left = Evaluate(root->children[0]);
            auto right = Evaluate(root->children[1]);
            auto plus = GetDisplayGroupFromText(root->value, Token(TokenType::NULLVAL, "0"));

            auto combine = this->MergeGroupToRight(this->MergeGroupToRight(left, plus), right);
            combine.prevToken = Token(root->type, root->value);
            
            return combine;
        } else { //unary
            auto left = Evaluate(root->children[0]);
            if (left.prevToken.type != TokenType::NUMBER && 
                    parser->GetPrecedence(left.prevToken) < parser->GetPrecedence(Token(root->type, root->value))) {
                left = this->ParenthesizeGroup(left);
            }
            std::string value = (root->type == TokenType::ADDITION) ? "+" : "-";

            auto sign = this->GetDisplayGroupFromText(value, Token(TokenType::NULLVAL, "0"));
            auto combine = this->MergeGroupToRight(sign, left);

            combine.prevToken = Token(root->type, root->value);
            return combine;
        }
    }

    //multiplication
    if (root->type == TokenType::MULTIPLICATION) {
        auto left = Evaluate(root->children[0]);
        auto right = Evaluate(root->children[1]);

        bool parenthesizeLeft = false;
        if ((left.prevToken.type != TokenType::NUMBER && parser->GetPrecedence(left.prevToken) < parser->GetPrecedence(Token(root->type, root->value)))
            || left.prevToken.value == "unary") {
            left = this->ParenthesizeGroup(left);
            parenthesizeLeft = true;
        }

        bool parenthesizeRight = false;
        if ((right.prevToken.type != TokenType::NUMBER && parser->GetPrecedence(right.prevToken) < parser->GetPrecedence(Token(root->type, root->value)))
            || right.prevToken.value == "unary") {
            right = this->ParenthesizeGroup(right);
            parenthesizeRight = true;
        }

        //no need for multiplication sign
        if ((parenthesizeLeft && parenthesizeRight) ||
            (parenthesizeLeft && right.prevToken.type == TokenType::NUMBER) ||
            (left.prevToken.type == TokenType::NUMBER && parenthesizeRight)
        ) {
            auto combine = this->MergeGroupToRight(left, right);
            combine.prevToken = Token(root->type, root->value);

            return combine;
        }

        //need multiplication sign
        else {
            auto sign = this->GetDisplayGroupFromText(".", Token(TokenType::NULLVAL, "0"));
            auto combine = this->MergeGroupToRight(this->MergeGroupToRight(left, sign), right);
            combine.prevToken = Token(root->type, root->value);

            return combine;
        }
    }

    //division
    if (root->type == TokenType::DIVISION) {
        auto first = Evaluate(root->children[0]);
        auto second = Evaluate(root->children[1]);

        auto midline = this->GetDisplayGroupFromRec(std::max(first.GetTotalWidth(), second.GetTotalWidth()) + this->lineWidthBuffer,
            Token(TokenType::NULLVAL, "0"));

        auto combine = this->MergeGroupToBottom(this->MergeGroupToBottom(first, midline), second);
        combine.prevToken = Token(root->type, root->value);

        return combine;
    }

    //trig functions
    if (root->type == TokenType::SINE) {

    }

    //catch all
    return DisplayGroup({}, Token(TokenType::NULLVAL, "0"));
}

//helper functions
//get group from single text
DisplayGroup ExpressionVisual::GetDisplayGroupFromText(std::string text, Token prevToken) {
    DisplayElement* newElement = this->textManager->CreateDisplayText(text);
    DisplayGroup newDisplayGroup({newElement}, prevToken);

    return newDisplayGroup;
}

//get group from single rec
DisplayGroup ExpressionVisual::GetDisplayGroupFromRec(int width, Token prevToken) {
    DisplayElement* newElement = this->recManager->CreateDisplayRectangle(width);
    DisplayGroup newDisplayGroup({newElement}, prevToken);

    return newDisplayGroup;
}

//merge group second to right of group "first"
DisplayGroup ExpressionVisual::MergeGroupToRight(DisplayGroup first, DisplayGroup second) {
    //adjust y value 
    if (first.GetTotalHeight() > second.GetTotalHeight()) {
        second.moveY((first.GetTotalHeight() - second.GetTotalHeight()) / 2);
    } else if (first.GetTotalHeight() < second.GetTotalHeight()) {
        first.moveY((second.GetTotalHeight() - first.GetTotalHeight()) / 2);
    }

    //move second group
    second.moveX(first.GetTotalWidth() + this->horizontalBuffer);
    first.Merge(second);

    return first;
}

DisplayGroup ExpressionVisual::MergeGroupToBottom(DisplayGroup first, DisplayGroup second) {
    //adjust x value
    if (first.GetTotalWidth() > second.GetTotalWidth()) {
        second.moveX((first.GetTotalWidth() - second.GetTotalWidth()) / 2);
    } else if (first.GetTotalWidth() < second.GetTotalWidth()) {
        first.moveX((second.GetTotalWidth() - first.GetTotalWidth()) / 2);
    }

    //move second group
    second.moveY(first.GetTotalHeight() + this->verticalBuffer);
    first.Merge(second);

    return first;
}

DisplayGroup ExpressionVisual::ParenthesizeGroup(DisplayGroup group) {
    int height = group.GetTotalHeight();
    auto leftParen = this->GetDisplayGroupFromText("(", Token(TokenType::NULLVAL, "0"));
    auto rightParen = this->GetDisplayGroupFromText(")", Token(TokenType::NULLVAL, "0"));

    float scale = ((float) height / leftParen.GetTotalHeight());
    leftParen.Scale(scale);
    rightParen.Scale(scale);

    return this->MergeGroupToRight(this->MergeGroupToRight(leftParen, group), rightParen);
}