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

#include "../Reuseable/managertemplateclass.h"
#include "../Reuseable/templateclass.h"

class ExpressionManager : Monobehaviour<sf::RenderWindow*> {
    protected:
        std::vector<std::shared_ptr<Expression>> controlledComponents;

    public:
        ExpressionManager() {
            this->controlledComponents.reserve(100000);
        }

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        std::weak_ptr<Expression> AddNewControlledComponent(std::shared_ptr<Expression> exp) {
            this->controlledComponents.push_back(exp);
            std::weak_ptr<Expression> observer = exp;

            return observer;
        }

        std::weak_ptr<Expression> GetControlledComponent(int idx) {
            if (idx < 0 || idx >= (int) this->controlledComponents.size()) {
                return std::weak_ptr<Expression>();
            }

            std::weak_ptr<Expression> observer = this->controlledComponents[idx];
            return observer;
        }

        //helper functions
        template <typename T>
        std::weak_ptr<Expression> AddConvertibleExpression(T exp) {
            try {
                auto pt = this->AddNewControlledComponent(std::static_pointer_cast<Expression>(std::make_shared<T>(exp)));
                return pt;
            } catch(const std::exception& e) {
                std::cerr << "Class cannot be convert to generic Expression type. Please recheck!";
                throw new std::bad_cast();
            }
        }
};

#endif