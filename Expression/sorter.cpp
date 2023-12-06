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

bool ExpressionSorter::OrderRelation(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v) {

}

bool ExpressionSorter::Equal(const std::weak_ptr<Expression> u, const std::weak_ptr<Expression> v) {
    auto p1 = u.lock();
    auto p2 = v.lock();

    if (p1 && p2) {
        auto type1 = p1.get()->GetType();
        auto type2 = p2.get()->GetType();

        if (type1 != type2) {
            return false;
        }

        if (type1 == ExpressionType::Undefined) {
            return true;
        }

        if (type1 == ExpressionType::Integer) {
            auto val1 = std::get<int>(p1.get()->GetValue());
            auto val2 = std::get<int>(p2.get()->GetValue());

            return val1 == val2;
        }

        if (type1 == ExpressionType::Symbol) {
            auto val1 = std::get<std::string>(p1.get()->GetValue());
            auto val2 = std::get<std::string>(p2.get()->GetValue());

            return val1 == val2;
        }

        if (type1 == ExpressionType::FracOp) {
            auto val1 = std::get<std::pair<int, int>>(p1.get()->GetValue());
            auto val2 = std::get<std::pair<int, int>>(p2.get()->GetValue());

            return val1 == val2;
        }
        
        int n = p1.get()->subexpressions.size();
        if (p1.get()->subexpressions.size() != p2.get()->subexpressions.size()) {
            return false;
        }

        bool isEqual = true;
        for (int i = 0; i < n; i++) {
            if (!this->Equal(p1.get()->subexpressions[i], p2.get()->subexpressions[i])) {
                isEqual = false;
                break;
            }
        }

        return isEqual;
    }

    return false;
}