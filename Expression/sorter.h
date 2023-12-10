#ifndef H_EXPRESSIONSORTER
#define H_EXPRESSIONSORTER

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "expressionmanager.h"
#include "expression.h"
#include "simplifyrational.h"

#include "../Reuseable/templateclass.h"
#include "Types/undefinedexp.h"
#include "Types/prodexp.h"
#include "Types/powexp.h"
#include "Types/integerexp.h"
#include "Types/fracexp.h"
#include "Types/sumexp.h"

class ExpressionSorter: Monobehaviour<sf::RenderWindow*, ExpressionManager*, SimplifyRational*> {
    public:
        sf::RenderWindow* window;
        ExpressionManager* expressionManager;
        SimplifyRational* simplifyRational;

        void Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager, SimplifyRational* simplifyRational) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        std::weak_ptr<Expression> Base(std::weak_ptr<Expression> u);
        std::weak_ptr<Expression> Exponent(std::weak_ptr<Expression> u);
        std::weak_ptr<Expression> Term(std::weak_ptr<Expression> u);
        std::weak_ptr<Expression> Constant(std::weak_ptr<Expression> u);

        bool OrderRelation(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v);
        bool Equal(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v);

        void SortExpression(std::weak_ptr<Expression> u);
        void RecursiveSortExpression(std::weak_ptr<Expression> u);

    private:
        

};

#endif