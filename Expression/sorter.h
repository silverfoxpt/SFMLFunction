#ifndef H_SORTER
#define H_SORTER

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

#include "../Reuseable/templateclass.h"
#include "Types/undefinedexp.h"
#include "Types/prodexp.h"
#include "Types/integerexp.h"
#include "Types/fracexp.h"

class ExpressionSorter: Monobehaviour<sf::RenderWindow*, ExpressionManager*> {
    public:
        sf::RenderWindow* window;
        ExpressionManager* expressionManager;

        void Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager) override;
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

    private:
        

};

#endif