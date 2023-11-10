#include "recmanager.h"

void RectangleElementManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void RectangleElementManager::Update(sf::Event event) {
}

void RectangleElementManager::Visualize(sf::Event event) {
    for (auto rec: this->controlledComponents) {
        rec.Draw(this->window);
    }
}

void RectangleElementManager::LateUpdate() {

}

void RectangleElementManager::Reset() {
    this->controlledComponents.clear();
    this->controlledComponents.reserve(100000);
}