#ifndef H_AUTOSIMPLIFY
#define H_AUTOSIMPLIFY

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <deque>

#include "expressionmanager.h"
#include "expression.h"
#include "simplifyrational.h"
#include "sorter.h"

#include "../Reuseable/templateclass.h"
#include "Types/undefinedexp.h"
#include "Types/prodexp.h"
#include "Types/powexp.h"
#include "Types/integerexp.h"
#include "Types/fracexp.h"
#include "Types/sumexp.h"

class ExpressionAutoSimplify: Monobehaviour<sf::RenderWindow*, ExpressionManager*, SimplifyRational*, ExpressionSorter*> {
    public:
        sf::RenderWindow* window;
        ExpressionManager* expressionManager;
        SimplifyRational* simplifyRational;
        ExpressionSorter* expressionSorter;

        void Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager, 
            SimplifyRational* simplifyRational, ExpressionSorter* expressionSorter) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        std::weak_ptr<Expression> AutoSimplify(std::weak_ptr<Expression> u);

    private:
        std::weak_ptr<Expression> SimplifyPower(std::weak_ptr<Expression> u);
        std::weak_ptr<Expression> SimplifyIntegerPower(std::weak_ptr<Expression> v, std::weak_ptr<Expression> w);

        std::weak_ptr<Expression> SimplifyProduct(std::weak_ptr<Expression> u);
        std::weak_ptr<Expression> SimplifySum(std::weak_ptr<Expression> u);
};

#endif