#include "textelement.h"

TextElement::TextElement(std::string text, sf::Font &font) {
    tex.setString(text);
    tex.setFont(font);

    tex.setFillColor(sf::Color::White);
    tex.setCharacterSize(30);
    
    //VERY IMPORTANT LINE :) 
    //Put text origin back to its true bound: https://en.sfml-dev.org/forums/index.php?topic=20284.0
    //Always put this at last, after setting size and font
    this->SetHardOrigin();
}

void TextElement::SetHardOrigin() {
    //std::cout << tex.getGlobalBounds().left << " " <<  tex.getGlobalBounds().top << '\n';
    tex.setOrigin(sf::Vector2f(tex.getGlobalBounds().left, tex.getGlobalBounds().top) - this->GetPosition()); 
}

void TextElement::Scale(float sc) {
    float curHeight = this->GetHeight();
    float needed = curHeight * sc;
    
    int point = this->tex.getCharacterSize();
    while (curHeight < needed) {
        point++;
        this->tex.setCharacterSize(point);
        curHeight = this->GetHeight();
    }
    while (curHeight > needed) {
        point--;
        this->tex.setCharacterSize(point);
        curHeight = this->GetHeight();
    }
    this->SetHardOrigin();
    
    std::cout << this->GetPosition().x << " " << this->GetPosition().y << '\n';
}

void TextElement::SetPosition(sf::Vector2f pos) {
    this->tex.setPosition(pos);
}

void TextElement::Move(sf::Vector2f dir) {
    this->SetPosition(this->GetPosition() + dir);
}

void TextElement::Draw(sf::RenderWindow* window) {
    window->draw(this->tex);
}

sf::Vector2f TextElement::GetPosition() {
    return tex.getPosition();
}

float TextElement::GetHeight() {
    return tex.getGlobalBounds().height;
}

float TextElement::GetWidth() {
    return tex.getGlobalBounds().width;
}

float TextElement::GetBottomX() {
    return this->GetPosition().x + this->GetWidth();
}

float TextElement::GetBottomY() {
    return this->GetPosition().y + this->GetHeight();
}