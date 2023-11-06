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

TextElement* TextElementManager::AddNewControlledComponent(TextElement child) {
    if (this->controlledComponents.size() >= this->maxElement) {
        std::cerr << "TextElementManager: Overflow. Please resize array." << '\n';
        return nullptr;
    }

    this->controlledComponents.push_back(child);
    return &this->controlledComponents[this->controlledComponents.size()-1];
}

TextElement* TextElementManager::GetControlledComponent(int idx) {
    if (idx < 0 || idx >= this->controlledComponents.size()) {
        return nullptr;
    }

    return &this->controlledComponents[idx];
}