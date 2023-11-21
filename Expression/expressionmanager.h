#ifndef H_EXPRESSIONMANAGER
#define H_EXPRESSIONMANAGER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "expression.h"
#include "integerexp.h"

#include "../Reuseable/managertemplateclass.h"
#include "../Reuseable/templateclass.h"

class ExpressionManager : Monobehaviour<sf::RenderWindow*>, Manager<Expression> {
    public:
        ExpressionManager() : Manager() {}

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;
};

#endif