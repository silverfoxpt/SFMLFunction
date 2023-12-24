#include "displaygroup.h"

int DisplayGroup::GetTotalHeight() {
    int h = 0;
    for (auto tex: this->elements) {
        h = std::max((float) h, tex->GetBottomY());
    }
    return h;
}

int DisplayGroup::GetTotalWidth() {
    int w = 0;
    for (auto tex: this->elements) {
        w = std::max((float) w, tex->GetBottomX());
    }
    return w;
}

int DisplayGroup::GetTopX() {
    int x = 1e9;
    for (auto tex: this->elements) {
        x = std::min((float) x, tex->GetPosition().x);
    }
    return x;
}

int DisplayGroup::GetTopY() {
    int y = 1e9;
    for (auto tex: this->elements) {
        y = std::min((float) y, tex->GetPosition().y);
    }
    return y;
}

sf::Vector2f DisplayGroup::GetTop() {
    return sf::Vector2f(this->GetTopX(), this->GetTopY());
}

void DisplayGroup::Scale(float sc) {
    for (auto tex: this->elements) {
        sf::Vector2f newPos = (tex->GetPosition() - this->GetTop()) * (sc);

        tex->Scale(sc);
        tex->SetPosition(newPos);
    }

    this->anchorHeight *= sc;
}

void DisplayGroup::moveX(float x) {
    for (auto tex: this->elements) {
        tex->Move(sf::Vector2f(x, 0));
    }
}

void DisplayGroup::moveY(float y) {
    for (auto tex: this->elements) {
        tex->Move(sf::Vector2f(0, y));
    }

    this->anchorHeight += y;
}

void DisplayGroup::Merge(DisplayGroup other) {
    for (auto tex: other.elements) {
        this->elements.push_back(tex);
    }
}

void DisplayGroup::SetPosition(sf::Vector2f pos) {
    this->moveX(this->GetTopX() - pos.x);
    this->moveY(this->GetTopY() - pos.y);
}