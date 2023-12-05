#include "sorter.h"

void ExpressionSorter::Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager) {
    this->window = window;  
    this->expressionManager = expressionManager;
}

void ExpressionSorter::Update(sf::Event event) {
}

void ExpressionSorter::Visualize(sf::Event event) {

}

void ExpressionSorter::LateUpdate() {

}

void ExpressionSorter::Reset() {

}

std::weak_ptr<Expression> ExpressionSorter::Base(std::weak_ptr<Expression> u) {
    if (auto pt = u.lock()) {
        auto type = pt.get()->GetType();
        if (type == ExpressionType::Integer || type == ExpressionType::FracOp) {
            return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
        }

        if (type == ExpressionType::PowOp) {
            return pt.get()->subexpressions[0];
        } 

        return u;
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

std::weak_ptr<Expression> ExpressionSorter::Exponent(std::weak_ptr<Expression> u) {
    if (auto pt = u.lock()) {
        auto type = pt.get()->GetType();
        if (type == ExpressionType::Integer || type == ExpressionType::FracOp) {
            return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
        }

        if (type == ExpressionType::PowOp) {
            return pt.get()->subexpressions[1];
        } 

        return this->expressionManager->AddConvertibleExpression(IntegerExpression(1));
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

std::weak_ptr<Expression> ExpressionSorter::Term(std::weak_ptr<Expression> u) {
    if (auto pt = u.lock()) {
        auto type = pt.get()->GetType();
        if (type == ExpressionType::Integer || type == ExpressionType::FracOp) {
            return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
        }

        if (type == ExpressionType::ProdOp) {
            auto first = pt.get()->subexpressions[0];
            if (auto p2 = first.lock()) {
                std::vector<std::weak_ptr<Expression>> terms;
                bool includeFirstTerm = !(p2.get()->isConstant());

                for (int i = ((includeFirstTerm) ? 0 : 1); i < (int) pt.get()->subexpressions.size(); i++) {
                    terms.push_back(pt.get()->subexpressions[i]);
                }

                ProductExpression prod("*");
                prod.AddSubexpression(terms);

                return this->expressionManager->AddConvertibleExpression(prod);
            } else {
                return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
            }
        }

        return u;
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

std::weak_ptr<Expression> ExpressionSorter::Constant(std::weak_ptr<Expression> u) {
    if (auto pt = u.lock()) {
        auto type = pt.get()->GetType();
        if (type == ExpressionType::Integer || type == ExpressionType::FracOp) {
            return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
        }

        if (type == ExpressionType::ProdOp) {
            auto first = pt.get()->subexpressions[0];
            if (auto p2 = first.lock()) {
                if (p2.get()->isConstant()) {
                    auto val = p2.get()->GetValue();
                    if (p2.get()->GetType() == ExpressionType::Integer) {
                        return this->expressionManager->AddConvertibleExpression(IntegerExpression(
                            std::get<int>(val)
                        ));
                    } else {
                        return this->expressionManager->AddConvertibleExpression(FractionExpression(
                            std::get<std::pair<int, int>>(val)
                        ));
                    }
                } 
                
                else {
                    return this->expressionManager->AddConvertibleExpression(IntegerExpression(1));
                }
            } else {
                return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
            }
        }

        return this->expressionManager->AddConvertibleExpression(IntegerExpression(1));
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}