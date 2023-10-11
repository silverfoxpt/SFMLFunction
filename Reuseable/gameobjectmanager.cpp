#include "gameobjectmanager.h"

GameobjectManager* GameobjectManager::instance = nullptr;

void GameobjectManager::Initialize(sf::RenderWindow* window) {
    this->window = window;
    this->controlledComponents.reserve(100000);
}

void GameobjectManager::Update(sf::Event event) {
    for (auto& obj: this->controlledComponents) {
        obj.Update(event);
    }
}

void GameobjectManager::Visualize(sf::Event event) {
    for (auto& obj: this->controlledComponents) {
        obj.Visualize(event);
    }
}

void GameobjectManager::LateUpdate() {
    for (auto& obj: this->controlledComponents) {
        obj.LateUpdate();
    }
}

void GameobjectManager::Reset() {
    for (auto& obj: this->controlledComponents) {
        obj.Reset();
    }
}

GameObject* GameobjectManager::GetControlledComponent(int idx) {
    if (idx < 0 || idx > (int) this->controlledComponents.size()) { std::cout << "NULL!" << '\n'; return nullptr;}
    return &this->controlledComponents[idx];
}

GameObject* GameobjectManager::AddNewControlledComponent(GameObject obj) { 
    //always initialize
    obj.Initialize(this->window);

    int idx = this->controlledComponents.size();
    this->controlledComponents.push_back(obj);

    return this->GetControlledComponent(idx);
}