#include "autosimplify.h"

void ExpressionAutoSimplify::Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager, 
    SimplifyRational* simplifyRational, ExpressionSorter* expressionSorter) 
{
    this->window = window;
    this->expressionManager = expressionManager;
    this->simplifyRational = simplifyRational;
    this->expressionSorter = expressionSorter;
}

void ExpressionAutoSimplify::Update(sf::Event event) {
}

void ExpressionAutoSimplify::Visualize(sf::Event event) {

}

void ExpressionAutoSimplify::LateUpdate() {

}

void ExpressionAutoSimplify::Reset() {

}

std::weak_ptr<Expression> ExpressionAutoSimplify::AutoSimplify(std::weak_ptr<Expression> u) {
    auto pt = u.lock();
    if (pt) {
        auto type = pt.get()->GetType();
        if (type == ExpressionType::Undefined) {
            return u;
        }

        if (type == ExpressionType::Integer || type == ExpressionType::Symbol) {
            return u;
        }

        if (type == ExpressionType::FracOp) {
            return this->simplifyRational->SimplifyRationalNumber(u);
        }
         
        //recursive simplification
        std::vector<std::weak_ptr<Expression>> simplifySub;
        for (auto sub: pt.get()->subexpressions) {
            simplifySub.push_back(this->AutoSimplify(sub));
        }
        pt.get()->subexpressions = simplifySub;

        //power simplification
        if (type == ExpressionType::PowOp) {
            return this->SimplifyPower(u);
        }

        //product simplification
        if (type == ExpressionType::ProdOp) {
            return this->SimplifyProduct(u);
        }

        //if everything fail
        return u;
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

std::weak_ptr<Expression> ExpressionAutoSimplify::SimplifyPower(std::weak_ptr<Expression> u) {
    auto pt = u.lock();
    auto v = pt.get()->subexpressions[0];
    auto w = pt.get()->subexpressions[1];

    auto p1 = v.lock();
    auto p2 = w.lock();

    if (p1 && p2) {
        auto type1 = p1.get()->GetType();
        auto type2 = p2.get()->GetType();

        auto val1 = p1.get()->GetValue();
        auto val2 = p2.get()->GetValue();

        //Rule SPOW - 1
        if (type1 == ExpressionType::Undefined || type2 == ExpressionType::Undefined) {
            return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
        }

        //Rule SPOW - 2
        if (type1 == ExpressionType::Integer) {
            // if v == 0
            if (this->simplifyRational->CompareRational(v, this->expressionManager->AddConvertibleExpression(IntegerExpression(0))) == 0) {
                //if w is not a constant -> Undefined
                if (!p2.get()->isConstant()) {
                    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
                }

                // if w > 0
                if (this->simplifyRational->CompareRational(w, this->expressionManager->AddConvertibleExpression(IntegerExpression(0))) == 1) {
                    return this->expressionManager->AddConvertibleExpression(IntegerExpression(0));
                } else {
                    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
                }
            }
        }

        //Rule SPOW - 3
        if (type1 == ExpressionType::Integer) {
            // if v == 1
            if (this->simplifyRational->CompareRational(v, this->expressionManager->AddConvertibleExpression(IntegerExpression(1))) == 0) {
                return this->expressionManager->AddConvertibleExpression(IntegerExpression(1));
            }
        }

        //Rule SPOW - 4
        if (type2 == ExpressionType::Integer) {
            return this->SimplifyIntegerPower(v, w);
        }

        //Rule SPOW - 5
        return u;
    } 

    else {
        return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
    }
}

std::weak_ptr<Expression> ExpressionAutoSimplify::SimplifyIntegerPower(std::weak_ptr<Expression> v, std::weak_ptr<Expression> w) {
    auto p1 = v.lock();
    auto p2 = w.lock();
    
    auto type1 = p1.get()->GetType();
    auto val2 = std::get<int>(p2.get()->GetValue());

    //Rule SINTPOW - 1
    if (p1.get()->isConstant()) {
        PowerExpression powe("^");
        powe.AddSubexpression({v, w});

        return this->simplifyRational->SimpilfyRNE(
            this->expressionManager->AddConvertibleExpression(powe)
        );
    }

    //Rule SINTPOW - 2
    if (val2 == 0) {
        return this->expressionManager->AddConvertibleExpression(IntegerExpression(1));
    }

    //Rule SINTPOW - 3
    if (val2 == 1) {
        return v;
    }

    //Rule SINTPOW - 4
    if (type1 == ExpressionType::PowOp) { // v = r^s
        auto r = p1.get()->subexpressions[0];
        auto s = p1.get()->subexpressions[1];

        ProductExpression prod("*");
        prod.AddSubexpression({s, w});

        //u = v^w = (r^s)^n = r^(s*n) = r^p
        auto p = this->SimplifyProduct(this->expressionManager->AddConvertibleExpression(prod)); 

        auto p3 = p.lock();
        if (p3) {
            auto type3 = p3.get()->GetType();

            //u = r^p
            if (type3 == ExpressionType::Integer) {
                return this->SimplifyIntegerPower(r, p); 
            } else {
                PowerExpression powe("^");
                powe.AddSubexpression({r, p});

                return this->expressionManager->AddConvertibleExpression(powe);
            }
        } else {
            return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
        }
    }

    //Rule SINTPOW - 5
    if (type1 == ExpressionType::ProdOp) { //v = v1.v2...vn -> v^w = (v1.v2...vn)^w = v1^w * v2^w *...*vn ^ w
        std::vector<std::weak_ptr<Expression>> simplifySub;

        for (auto sub: p1.get()->subexpressions) {
            simplifySub.push_back(this->SimplifyIntegerPower(sub, w));
        }

        ProductExpression prod("*");
        prod.AddSubexpression(simplifySub);

        return this->expressionManager->AddConvertibleExpression(prod);
    }

    //Rule SINTPOW - 6
    PowerExpression powe("^");
    powe.AddSubexpression({v, w}); //u = v^w

    return this->expressionManager->AddConvertibleExpression(powe);
}

std::weak_ptr<Expression> ExpressionAutoSimplify::SimplifyProduct(std::weak_ptr<Expression> u) {
    auto p1 = u.lock();

    if (p1) {
        auto subs = p1.get()->subexpressions;

        //Rule SPRD - 0
        if (subs.size() == 0) {
            return this->expressionManager->AddConvertibleExpression(IntegerExpression(1));
        }

        //Rule SPRD - 1
        for (auto sub: subs) {
            auto pt = sub.lock();
            if (pt) {
                if (pt.get()->GetType() == ExpressionType::Undefined) {
                    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
                }
            }
        }

        //Rule SPRD - 2
        for (auto sub: subs) {
            auto pt = sub.lock();
            if (pt) {
                if (pt.get()->GetType() == ExpressionType::Integer) {
                    int val = std::get<int>(pt.get()->GetValue());
                    if (val == 0) {
                        return this->expressionManager->AddConvertibleExpression(IntegerExpression(0));
                    }
                }
            }
        }

        //Rule SPRD - 3
        if (subs.size() == 1) {
            return subs[0];
        }

        //Rule SPRD - 4 -> Reduce
        this->expressionSorter->SortExpression(u);
        std::vector<std::weak_ptr<Expression>> res; res.push_back(subs[0]);

        for (int i = 1; i < subs.size(); i++) {
            auto first = res.back();
            auto sec = subs[i];

            auto pa = first.lock(), pb = sec.lock();
            if (pa && pb) {
                //case which both are constant
                if (pa.get()->isConstant() && pb.get()->isConstant()) {
                    ProductExpression prod("*");
                    prod.AddSubexpression({first, sec});

                    res.pop_back();
                    res.push_back(this->simplifyRational->SimpilfyRNE(
                        this->expressionManager->AddConvertibleExpression(prod)
                    ));
                }

                //case which one is constant and one is not
                else if (pa.get()->isConstant() && (!pb.get()->isConstant())) {
                    res.push_back(sec); continue;
                }

                //case which both are not constant
                else {
                    auto base1 = this->expressionSorter->Base(first);

                    //case of A^X + A^Y = A^(X+Y)
                    if (this->expressionSorter->Equal(base1, this->expressionSorter->Base(sec))) {
                        auto exp1 = this->expressionSorter->Exponent(first);
                        auto exp2 = this->expressionSorter->Exponent(sec);

                        SumExpression sums("+");
                        sums.AddSubexpression({exp1, exp2});

                        auto trueExp = this->SimplifySum(this->expressionManager->AddConvertibleExpression(sums));

                        PowerExpression pows("^");
                        pows.AddSubexpression({base1, trueExp});

                        res.pop_back();
                        res.push_back(this->SimplifyPower(this->expressionManager->AddConvertibleExpression(pows)));
                    }
                    
                    //there's nothing else left to check
                    else {
                        res.push_back(sec); continue;
                    }
                }
            } 

            else {
                return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
            }
        }

        //TO DO: Remove all redundant 1s. That means, if there is more than one 1s in the operators list, it shouldn't be there
        //This can happen when two operator that is not constant blow up each other: a^-1 * a = 1

        bool diffThan1 = false;
        auto onlyone = this->expressionManager->AddConvertibleExpression(IntegerExpression(1));

        for (int i = 0; i < res.size(); i++) {
            if (!this->expressionSorter->Equal(res[i], onlyone)) {
                diffThan1 = true; break;
            }
        }

        if (diffThan1) { //remove all ones
            std::vector<std::weak_ptr<Expression>> res2;
            for (int i = 0; i < res.size(); i++) {
                if (!this->expressionSorter->Equal(res[i], onlyone)) {
                    res2.push_back(res[i]);
                }
            }

            if (res2.size() == 1) {
                return res2[0];
            }

            else {
                ProductExpression prod("*");
                prod.AddSubexpression(res2);

                return this->expressionManager->AddConvertibleExpression(prod);
            }
        } 
        
        else { //returning one 1 is enough
            return onlyone;
        }
    }

    else {
        return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
    }
}

std::weak_ptr<Expression> ExpressionAutoSimplify::SimplifySum(std::weak_ptr<Expression> u) { 
    return u;
}