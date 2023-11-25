#ifndef H_SIMPLIFYRATIONAL
#define H_SIMPLIFYRATIONAL

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "../Reuseable/templateclass.h"
#include "expression.h"
#include "Types/integerexp.h"
#include "Types/fracexp.h"
#include "Types/undefinedexp.h"

#include "expressionmanager.h"


class SimplifyRational: Monobehaviour<sf::RenderWindow*, ExpressionManager*> {
    public:
        sf::RenderWindow* window;
        ExpressionManager* expressionManager;

        void Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        std::weak_ptr<Expression> SimplifyRationalNumber(std::weak_ptr<Expression> rational);

    private:
        int gcd(int a, int b);
};

#endif