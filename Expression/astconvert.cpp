#include "astconvert.h"

void ASTConverter::Initialize(sf::RenderWindow* window, ASTParser* parser, ExpressionManager* manager) {
    this->window = window;
    this->mainParser = parser;
    this->expressionManager = manager;
}

void ASTConverter::Update(sf::Event event) {
}

void ASTConverter::Visualize(sf::Event event) {

}

void ASTConverter::LateUpdate() {

}

void ASTConverter::Reset() {

}

std::weak_ptr<Expression> ASTConverter::ConvertASTToExpressionTree(ASTNode* root) {
    if (root->type == TokenType::NUMBER) {
        //std::shared_ptr<IntegerExpression> tmp = std::make_shared<IntegerExpression>(IntegerExpression(std::stoi(root->value)));
        //std::shared_ptr<Expression> newNumber = std::static_pointer_cast<Expression>(tmp);
        //return this->expressionManager->AddNewControlledComponent(newNumber);
        return this->expressionManager->AddConvertibleExpression(IntegerExpression(std::stoi(root->value)));
    }
    
    if (root->type == TokenType::SYMBOL) {
        //std::shared_ptr<SymbolExpression> tmp = std::make_shared<SymbolExpression>(SymbolExpression(root->value));
        //std::shared_ptr<Expression> newSymbol = std::static_pointer_cast<Expression>(tmp);
        //return this->expressionManager->AddNewControlledComponent(newSymbol);

        return this->expressionManager->AddConvertibleExpression(SymbolExpression(root->value));
    } 

    if (root->type == TokenType::ADDITION) {
        if (root->value == "unary") { //deal with unary operator (same type as sum)
            auto first = this->ConvertASTToExpressionTree(root->children[0]); // +x = x
            return first;
        }

        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        SumExpression exp("+");
        exp.AddSubexpression({first, second});

        auto tmp = std::make_shared<SumExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::SUBTRACTION) {
        if (root->value == "unary") { //deal with - unary operator (same type as difference)
            auto first = this->expressionManager->AddNewControlledComponent(
                std::static_pointer_cast<Expression>(std::make_shared<IntegerExpression>(IntegerExpression(-1)))
            );
            auto second = this->ConvertASTToExpressionTree(root->children[0]);

            ProductExpression prod("*");
            prod.AddSubexpression({first, second}); // -x = (-1) * x

            return this->expressionManager->AddNewControlledComponent(
                std::static_pointer_cast<Expression>(std::make_shared<ProductExpression>(prod))
            );
        }

        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        auto third = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<IntegerExpression>(IntegerExpression(-1)))
        );

        ProductExpression prod("*");
        prod.AddSubexpression({third, second}); // -x = (-1) * x

        auto fourth = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<ProductExpression>(prod))
        );

        SumExpression exp("+");
        exp.AddSubexpression({first, fourth}); // a - b = a + (-1) * b

        auto tmp = std::make_shared<SumExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::MULTIPLICATION) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        ProductExpression exp("*");
        exp.AddSubexpression({first, second});

        auto tmp = std::make_shared<ProductExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::DIVISION) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        PowerExpression powy("^");
        auto third = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<IntegerExpression>(IntegerExpression(-1)))
        );
        powy.AddSubexpression({second, third});

        auto fourth = this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<PowerExpression>(powy))
        );

        ProductExpression exp("*");
        exp.AddSubexpression({first, fourth}); // a/b = a * (b^(-1))

        auto tmp = std::make_shared<ProductExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    if (root->type == TokenType::EXPONENTIATION) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);
        auto second = this->ConvertASTToExpressionTree(root->children[1]);

        PowerExpression exp("^");
        exp.AddSubexpression({first, second});

        auto tmp = std::make_shared<PowerExpression>(exp);
        return this->expressionManager->AddNewControlledComponent(std::static_pointer_cast<Expression>(tmp));
    }

    //functions down here
    if (Token::isFunction(root->type)) {
        auto first = this->ConvertASTToExpressionTree(root->children[0]);

        FunctionExpression exp(root->value, this->convertTypeFunction[root->type]);
        exp.AddSubexpression(first);

        return this->expressionManager->AddNewControlledComponent(
            std::static_pointer_cast<Expression>(std::make_shared<FunctionExpression>(exp))
        );
    }

    return std::weak_ptr<Expression>();
}

//only works for sanitized tree!
ASTNode* ASTConverter::ConvertExpressionTreeToAST(std::weak_ptr<Expression> root) {
    auto pt = root.lock();
    if (pt) {
        auto type = pt.get()->GetType();
        auto val = pt.get()->GetValue();
        auto subs = pt.get()->subexpressions;

        if (type == ExpressionType::Undefined) {
            ASTNode nullval("NULL", "NULL", TokenType::NULLVAL);
            auto newNode = this->mainParser->AddNewNode(nullval);

            return newNode;
        }

        else if (type == ExpressionType::Integer) {
            ASTNode num(std::to_string(std::get<int>(val)), "Integer", TokenType::NUMBER);
            auto newNode = this->mainParser->AddNewNode(num);

            return newNode;
        }

        else if (type == ExpressionType::FracOp) {
            auto twoPartVal = std::get<std::pair<int, int>>(val);
            auto first = this->ConvertExpressionTreeToAST(
                this->expressionManager->AddConvertibleExpression(IntegerExpression(twoPartVal.first))
            );
            auto sec = this->ConvertExpressionTreeToAST(
                this->expressionManager->AddConvertibleExpression(IntegerExpression(twoPartVal.second))
            );

            ASTNode frac("Quotient", "Quotient - Fraction", TokenType::DIVISION);
            frac.AddChild({first, sec});
            auto newNode = this->mainParser->AddNewNode(frac);

            return newNode;
        }

        else if (type == ExpressionType::Symbol) {
            ASTNode sym(std::get<std::string>(val), "Symbol", TokenType::SYMBOL);
            auto newNode = this->mainParser->AddNewNode(sym);

            return newNode;
        }

        else if (type == ExpressionType::SumOp) {
            auto first = this->ConvertExpressionTreeToAST(subs.back()); subs.pop_back();
            
            ASTNode* sec = nullptr;
            if (subs.size() >= 2) {
                SumExpression tmpSum("+"); tmpSum.AddSubexpression(subs);
                auto tmpExp = this->expressionManager->AddConvertibleExpression(tmpSum);
                sec = this->ConvertExpressionTreeToAST(tmpExp);
            } else { //only one left
                sec = this->ConvertExpressionTreeToAST(subs.back()); subs.pop_back();
            }

            //create node
            ASTNode sum(std::get<std::string>(val), "Sum", TokenType::ADDITION);
            sum.AddChild({first, sec});
            auto newNode = this->mainParser->AddNewNode(sum);

            return newNode;
        }

        else if (type == ExpressionType::ProdOp) {
            auto first = this->ConvertExpressionTreeToAST(subs.back()); subs.pop_back();

            ASTNode* sec = nullptr;
            if (subs.size() >= 2) {
                ProductExpression tmpProd("*"); tmpProd.AddSubexpression(subs);
                auto tmpExp = this->expressionManager->AddConvertibleExpression(tmpProd);
                sec = this->ConvertExpressionTreeToAST(tmpExp);
            } else { //only one left
                sec = this->ConvertExpressionTreeToAST(subs.back()); subs.pop_back();
            }

            //create node
            ASTNode prod(std::get<std::string>(val), "Product", TokenType::MULTIPLICATION);
            prod.AddChild({first, sec});
            auto newNode = this->mainParser->AddNewNode(prod);

            return newNode;
        }

        else if (pt.get()->isFunction()) {
            auto first = this->ConvertExpressionTreeToAST(subs.back());

            //create node
            ASTNode func(std::get<std::string>(val), "Function", this->convertTypeFunctionBackward[type]);
            func.AddChild({first});
            auto newNode = this->mainParser->AddNewNode(func);

            return newNode;
        }

        else if (type == ExpressionType::PowOp) {
            auto first = this->ConvertExpressionTreeToAST(subs[0]);
            auto sec = this->ConvertExpressionTreeToAST(subs[1]);

            //create node
            ASTNode powe(std::get<std::string>(val), "Power", TokenType::EXPONENTIATION);
            powe.AddChild({first, sec});
            auto newNode = this->mainParser->AddNewNode(powe);

            return newNode;
        }

        else {
            throw std::invalid_argument("ASTConverter::ConvertExpressionTreeToAST - Conversion type not found!");
        }
    }

    else {
        return nullptr;
    }
}

std::vector<std::weak_ptr<Expression>> ASTConverter::FlattenProductExpressionTree(std::weak_ptr<Expression> root) {
    if (auto pt = root.lock()) {
        if (pt.get()->GetType() != ExpressionType::ProdOp) { //not a Product tree
            for (auto child: pt.get()->subexpressions) {
                this->FlattenProductExpressionTree(child);
            }
            return {root};
        }

        std::vector<std::weak_ptr<Expression>> newSubexpressions; newSubexpressions.reserve(100); //safety i guess?
        for (auto child: pt.get()->subexpressions) {
            auto childSub = this->FlattenProductExpressionTree(child);
            for (auto exp: childSub) {
                newSubexpressions.push_back(exp);
            }
        }

        pt.get()->subexpressions = newSubexpressions;
        return newSubexpressions;
    }

    std::cerr << "Invalid/Deallocated Tree Found - FlattenProductExpressionTree" << '\n';
    return {root};
}   

std::vector<std::weak_ptr<Expression>> ASTConverter::FlattenSumExpressionTree(std::weak_ptr<Expression> root) {
    if (auto pt = root.lock()) {
        if (pt.get()->GetType() != ExpressionType::SumOp) { //not a Sum tree
            for (auto child: pt.get()->subexpressions) {
                this->FlattenSumExpressionTree(child);
            }
            return {root};
        }

        std::vector<std::weak_ptr<Expression>> newSubexpressions; newSubexpressions.reserve(100); //safety i guess?
        for (auto child: pt.get()->subexpressions) {
            auto childSub = this->FlattenSumExpressionTree(child);
            for (auto exp: childSub) {
                newSubexpressions.push_back(exp);
            }
        }

        pt.get()->subexpressions = newSubexpressions;
        return newSubexpressions;
    }

    std::cerr << "Invalid/Deallocated Tree Found - FlattenSumExpressionTree" << '\n';
    return {root};
}

void ASTConverter::Debug(std::weak_ptr<Expression> root, int level)  {
    if (auto pt = root.lock()) {
        for (int i = 1; i <= level; i++) {std::cout << "  ";}
        std::cout << pt.get()->GetDescription() << '\n';

        for (auto child: pt.get()->subexpressions) {
            Debug(child, level+1);
        }
    }
}