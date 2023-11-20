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

class ExpressionManager : Monobehaviour<sf::RenderWindow*> {
    public:
        std::vector<Expression> controlledComponents;
        ExpressionManager() {
            this->controlledComponents.reserve(100000);
        }

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        Expression* AddNewControlledComponent(Expression args) {
            if ((int) this->controlledComponents.size() >= this->maxElement) {
                std::cerr << "Manager: Overflow. Please resize array." << '\n';
                return nullptr;
            }

            this->controlledComponents.push_back(args);
            return &this->controlledComponents[this->controlledComponents.size()-1];
        }

        Expression* GetControlledComponent(int idx) {
            if (idx < 0 || idx >= (int) this->controlledComponents.size()) {
                return nullptr;
            }

            return &this->controlledComponents[idx];
        }

        const static int maxElement = 100000;
};

#endif