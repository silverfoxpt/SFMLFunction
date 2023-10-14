#ifndef H_RPN
#define H_RPN

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <set>

#include "../Reuseable/templateclass.h"

#include "RPN/stringhelp.h"

struct opRpn {
    std::string op;
    int priority;
    bool isPrefixOp;
};

class RPN : Monobehaviour<sf::RenderWindow*> {
    public:
        sf::RenderWindow* window;

        void Initialize(sf::RenderWindow* window) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        //helper
        std::vector<std::string> InfixToPostfix(std::string infix);

        //vars
        std::vector<opRpn> operators = {
            {"+", 1, false},
            {"-", 1, false},
            {"*", 2, false},
            {"/", 2, false},
            {"^", 3, false}
        };
    private:
        
};

#endif