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
        std::weak_ptr<Expression> SimpilfyRNE(std::weak_ptr<Expression> u);
        std::weak_ptr<Expression> SimpilfyRNERec(std::weak_ptr<Expression> u);

        //helper
        std::weak_ptr<Expression> EvaluateSum(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v);
        std::weak_ptr<Expression> EvaluateProduct(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v);
        std::weak_ptr<Expression> EvaluatePower(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v);

        int CompareRational(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v);
        int CompareRational(std::weak_ptr<Expression> u, float val);

    private:
        int gcd(int a, int b);
        float exp = 0.00001;
};

#endif