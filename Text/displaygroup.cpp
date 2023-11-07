#include "displaygroup.h"

int DisplayGroup::GetTotalHeight() {
    int h = 0;
    for (auto tex: this->elements) {
        h = std::max(h, (int) tex->GetBottomY());
    }
    return h;
}

int DisplayGroup::GetTotalWidth() {
    int w = 0;
    for (auto tex: this->elements) {
        w = std::max(w, (int) tex->GetBottomX());
    }
    return w;
}