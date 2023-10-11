#ifndef H_COMPONENTTEMPLATECLASS
#define H_COMPONENTTEMPLATECLASS

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "managertemplateclass.h"
#include "gameobject.h"

class GameObject;

class Component {
    public:
        virtual ~Component() = default;

        GameObject* parentObj;

        Component(GameObject* parent) {
            this->parentObj = parent;
        }
};

#endif