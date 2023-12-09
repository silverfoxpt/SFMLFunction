#include "sorter.h"

void ExpressionSorter::Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager, SimplifyRational* simplifyRational) {
    this->window = window;  
    this->expressionManager = expressionManager;
    this->simplifyRational = simplifyRational;
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

//return True if u's Order is smaller than v's Order, and False otherwise (even in case of equal)
bool ExpressionSorter::OrderRelation(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v) {
    auto p1 = u.lock();
    auto p2 = v.lock();

    if (p1 && p2) {
        auto type1 = p1.get()->GetType();
        auto type2 = p2.get()->GetType();

        if (type1 == ExpressionType::Undefined) {
            return true;
        }

        if (type2 == ExpressionType::Undefined) {
            return false;
        }

        //u is Constant
        if (p1.get()->isConstant()) {
            if (p2.get()->isConstant()) { // Rule O-1
                return (this->simplifyRational->CompareRational(u, v) == -1); //-1 -> u < v -> u's Order is smaller
            }
            
            //Constant is always < order than everything else, other than another Constant
            return true;
        }

        //u is Symbol
        if (type1 == ExpressionType::Symbol) {
            if (type2 == ExpressionType::Symbol) { // Rule O-2
                std::string val1 = std::get<std::string>(p1.get()->GetValue());
                std::string val2 = std::get<std::string>(p2.get()->GetValue());

                return val1 < val2; // lexicographical order
            }

            //Others - To the left - To be handled differently
            return (!(this->OrderRelation(v, u)));
        }

        //u is Product
        if (type1 == ExpressionType::ProdOp) {
            if (type2 == ExpressionType::ProdOp) { // Rule O-3
                int i = p1.get()->subexpressions.size()-1;
                int j = p2.get()->subexpressions.size()-1;

                while (i >= 0 && j >= 0) {
                    auto u1 = p1.get()->subexpressions[i];
                    auto v1 = p2.get()->subexpressions[j];

                    if (this->Equal(u1, v1)) {
                        i--; j--;
                        continue;
                    }

                    return this->OrderRelation(u1, v1);
                }

                //if everything checked out - Compare number of operands
                return p1.get()->subexpressions.size() < p2.get()->subexpressions.size();
            }

            else if (type2 == ExpressionType::PowOp || type2 == ExpressionType::SumOp || 
                     p2.get()->isFunction() || type2 == ExpressionType::Symbol) 
            {
                ProductExpression prod("*");
                prod.AddSubexpression(v);

                return this->OrderRelation(u, this->expressionManager->AddConvertibleExpression(prod));
            }

            //Others - To the left - To be handled differently
            return (!(this->OrderRelation(v, u)));
        }

        //u is Power
        if (type1 == ExpressionType::PowOp) {
            if (type2 == ExpressionType::PowOp) { //Rule O-4
                auto u1 = p1.get()->subexpressions[0];
                auto v1 = p2.get()->subexpressions[0];

                if (!this->Equal(u1, v1)) { //compare the bases
                    return this->OrderRelation(u1, v1);
                } else { //compare the exponents
                    return this->OrderRelation(p1.get()->subexpressions[1], p2.get()->subexpressions[1]);
                }
            }

            else if (type2 == ExpressionType::SumOp || p2.get()->isFunction() || type2 == ExpressionType::Symbol) {
                PowerExpression powe("^");
                powe.AddSubexpression(v);
                powe.AddSubexpression(this->expressionManager->AddConvertibleExpression(IntegerExpression(1)));

                //u <| v -> u <| v^1
                return this->OrderRelation(u, this->expressionManager->AddConvertibleExpression(powe));
            }

            //Others - To the left - To be handled differently
            return (!(this->OrderRelation(v, u)));
        }

        //u is Product
        if (type1 == ExpressionType::SumOp) {
            if (type2 == ExpressionType::SumOp) { // Rule O-3
                int i = p1.get()->subexpressions.size()-1;
                int j = p2.get()->subexpressions.size()-1;

                while (i >= 0 && j >= 0) {
                    auto u1 = p1.get()->subexpressions[i];
                    auto v1 = p2.get()->subexpressions[j];

                    if (this->Equal(u1, v1)) {
                        i--; j--;
                        continue;
                    }

                    return this->OrderRelation(u1, v1);
                }

                //if everything checked out - Compare number of operands
                return p1.get()->subexpressions.size() < p2.get()->subexpressions.size();
            }

            else if ( p2.get()->isFunction() || type2 == ExpressionType::Symbol) 
            {
                SumExpression sum("+");
                sum.AddSubexpression(v);

                return this->OrderRelation(u, this->expressionManager->AddConvertibleExpression(sum));
            }

            //Others - To the left - To be handled differently
            return (!(this->OrderRelation(v, u)));
        }

        if (p1.get()->isFunction()) {
            if (p2.get()->isFunction()) {
                std::string val1 = std::get<std::string>(p1.get()->GetValue());
                std::string val2 = std::get<std::string>(p2.get()->GetValue());

                if (val1 != val2) { //if two type of function is different
                    return val1 < val2; //return based on lexicographical order
                }

                else { //same to rule O-3 -> Compare all operands from right to left, if all match, compare number of operands
                    int i = p1.get()->subexpressions.size()-1;
                    int j = p2.get()->subexpressions.size()-1;

                    while (i >= 0 && j >= 0) {
                        auto u1 = p1.get()->subexpressions[i];
                        auto v1 = p2.get()->subexpressions[j];

                        if (this->Equal(u1, v1)) {
                            i--; j--;
                            continue;
                        }

                        return this->OrderRelation(u1, v1);
                    }

                    //if everything checked out - Compare number of operands
                    return p1.get()->subexpressions.size() < p2.get()->subexpressions.size();
                }
            }

            else if (type2 == ExpressionType::Symbol) {
                std::string val1 = std::get<std::string>(p1.get()->GetValue());
                std::string val2 = std::get<std::string>(p2.get()->GetValue());

                if (val1 == val2)  {
                    return false;
                } else {
                    return val1 < val2; //lexicographically between function's type and symbol string
                }
            }

            //Others - To the left - To be handled differently
            return (!(this->OrderRelation(v, u)));
        }

        return false;
    }

    return false;
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

void ExpressionSorter::SortExpression(std::weak_ptr<Expression> u) {
    if (auto pt = u.lock()) {
        auto& tmp = pt.get()->subexpressions;

        std::sort(tmp.begin(), tmp.end(), [this](const auto& a, const auto& b) {
            return this->OrderRelation(a, b);
        });
    }
}