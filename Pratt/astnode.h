#ifndef H_ASTNODE
#define H_ASTNODE

#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include "token.h"

class ASTNode {
    public:
        std::string value;
        std::string description;
        TokenType type;
        std::vector<ASTNode*> children;

        ASTNode() {
            this->value = "";
            this->description = "";
        }

        ASTNode(std::string value, std::string description, TokenType type) {
            this->value = value;
            this->description = description;
            this->type = type;
        }

        void AddChild(ASTNode* node) {
            this->children.push_back(node);
        }
};  

#endif