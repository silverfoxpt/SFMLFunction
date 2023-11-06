#include "textelementmanager.h"

void TextElementManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void TextElementManager::Update(sf::Event event) {
}

void TextElementManager::Visualize(sf::Event event) {
    for (auto tex: this->controlledComponents) {
        tex.Draw(this->window);
    }
}

void TextElementManager::LateUpdate() {

}

void TextElementManager::Reset() {

}