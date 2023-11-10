#include "rectangleelement.h"

void RectangleElement::SetPosition(sf::Vector2f pos) {
    this->shape.setPosition(pos);
}

void RectangleElement::Draw(sf::RenderWindow* window) {
    window->draw(shape);
}

void RectangleElement::Move(sf::Vector2f dir) {
    this->shape.setPosition(this->GetPosition() + dir);
}

void RectangleElement::Scale(float sc) {
    this->shape.scale(sf::Vector2f(sc, sc));
}

void RectangleElement::SetHardOrigin() {
    this->shape.setOrigin(sf::Vector2f(0, 0));
}

sf::Vector2f RectangleElement::GetPosition() {
    return this->shape.getPosition();
}

float RectangleElement::GetBottomX() {
    return this->GetPosition().x + this->GetWidth();
}

float RectangleElement::GetBottomY() {
    return this->GetPosition().y + this->GetHeight();
}

float RectangleElement::GetHeight() {
    return this->shape.getLocalBounds().height;
} 

float RectangleElement::GetWidth() {
    return this->shape.getLocalBounds().width;
} 