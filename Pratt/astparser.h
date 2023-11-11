#ifndef H_ASTPARSER
#define H_ASTPARSER

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
#include "../Reuseable/stringhelp.h"
#include "lexer.h"

#include "astnode.h"

struct ASTFunc {
    bool matched;
    ASTNode* value;
};

class ASTParser: Monobehaviour<sf::RenderWindow*, Lexer*> {
    public:
        sf::RenderWindow* window;
        Lexer* lex;
        std::vector<ASTNode> nodes; 

        void Initialize(sf::RenderWindow* window, Lexer* lex) override;
        void Update(sf::Event event) override;
        void Visualize(sf::Event event) override;
        void LateUpdate() override;
        void Reset() override;

        ASTNode* Parse(std::string input);
        ASTNode* Expression(int curPrecedence);
        ASTNode* PrefixHandler();

        ASTFunc TrigPrefixHandler();
        ASTNode* CurlyParenthesisHandler();

        ASTNode* InfixHandler(ASTNode* lhs, TokenType type);
        int GetPrecedence(Token token);

        ASTNode* AddNewNode(ASTNode node) {
            this->nodes.push_back(node);
            if (this->nodes.size() >= 100000) {
                throw std::overflow_error("Too many nodes! Please reduce the number of identifiers within expression!");
            } 
            return &this->nodes[this->nodes.size()-1];
        }

        void Debug(ASTNode* root, int level);

    private:
        std::map<std::string, int> precedence = {
            {"+", 2},
            {"-", 2},
            {"*", 3},
            {"/", 3},
            {"unary", 4},
            {"^", 5}
        };
        
};

#endif