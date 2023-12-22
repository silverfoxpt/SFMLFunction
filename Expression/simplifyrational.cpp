#include "simplifyrational.h"

void SimplifyRational::Initialize(sf::RenderWindow* window, ExpressionManager* expressionManager) {
    this->window = window;
    this->expressionManager = expressionManager;
}

void SimplifyRational::Update(sf::Event event) {
}

void SimplifyRational::Visualize(sf::Event event) {

}

void SimplifyRational::LateUpdate() {

}

void SimplifyRational::Reset() {

}

std::weak_ptr<Expression> SimplifyRational::SimplifyRationalNumber(std::weak_ptr<Expression> rational) {
    if (auto pt = rational.lock()) {
        if (pt.get()->GetType() == ExpressionType::Undefined) {
            return rational;
        }

        if (pt.get()->GetType() == ExpressionType::Integer) {
            return rational;
        }

        if (pt.get()->GetType() == ExpressionType::FracOp) {
            auto value = std::get<std::pair<int, int>>(pt.get()->GetValue());
            int nume = value.first, deno = value.second;

            if (deno == 0) {
                return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
            }

            if (nume % deno == 0) {
                return this->expressionManager->AddConvertibleExpression(IntegerExpression(nume/deno));
            }

            int gc = this->gcd(std::abs(nume), std::abs(deno));
            return this->expressionManager->AddConvertibleExpression(FractionExpression({nume / gc, deno / gc}));
        }

        return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
    }
    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

int SimplifyRational::gcd(int a, int b) {
    if (b == 0) {return a;}
    return this->gcd(b, a % b);
}

std::weak_ptr<Expression> SimplifyRational::SimpilfyRNE(std::weak_ptr<Expression> u) {
    auto v = this->SimpilfyRNERec(u);
    if(auto pt = v.lock()) {
        if (pt.get()->GetType() == ExpressionType::Undefined) {
            return v;
        }
        return this->SimplifyRationalNumber(v);
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

std::weak_ptr<Expression> SimplifyRational::SimpilfyRNERec(std::weak_ptr<Expression> u) {
    if (auto pt = u.lock()) {
        ExpressionType type = pt.get()->GetType();
        ValueVariant value = pt.get()->GetValue();

        if (type == ExpressionType::Undefined) {
            return u;
        }

        if (type == ExpressionType::Integer) {
            return u;
        }

        if (type == ExpressionType::FracOp) {
            return this->SimplifyRationalNumber(u);
        }

        if (type == ExpressionType::SumOp || type == ExpressionType::ProdOp) {
            std::weak_ptr<Expression> v = this->SimpilfyRNERec(pt.get()->subexpressions[0]);
            std::weak_ptr<Expression> w;
            int numOp = pt.get()->subexpressions.size();

            for (int i = 1; i < numOp; i++) {
                std::weak_ptr<Expression> w = this->SimpilfyRNERec(pt.get()->subexpressions[i]);
                auto v1 = v.lock();
                auto w1 = w.lock();

                if (v1 && w1) {
                    if (v1.get()->GetType() == ExpressionType::Undefined || w1.get()->GetType() == ExpressionType::Undefined) {
                        return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
                    }

                    else if (type == ExpressionType::SumOp) {
                        v = this->EvaluateSum(v, w);
                    }

                    else if (type == ExpressionType::ProdOp) {
                        v = this->EvaluateProduct(v, w);
                    }
                } 
            }

            return this->SimplifyRationalNumber(v);
        }

        if (type == ExpressionType::PowOp) {
            std::weak_ptr<Expression> v = this->SimpilfyRNERec(pt.get()->subexpressions[0]);
            std::weak_ptr<Expression> w = this->SimpilfyRNERec(pt.get()->subexpressions[1]);

            return this->EvaluatePower(v, w);
        }

        return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

std::weak_ptr<Expression> SimplifyRational::EvaluateSum(const std::weak_ptr<Expression> u, const std::weak_ptr<Expression> v) {
    auto u1 = u.lock();
    auto v1 = v.lock();

    if (u1 && v1) {
        std::pair<int, int> value1, value2;

        if (u1.get()->GetType() == ExpressionType::FracOp) {
            value1 = std::get<std::pair<int, int>>(u1.get()->GetValue());
        } else {
            value1 = {std::get<int>(u1.get()->GetValue()), 1};
        }

        if (v1.get()->GetType() == ExpressionType::FracOp) {
            value2 = std::get<std::pair<int, int>>(v1.get()->GetValue());
        } else {
            value2 = {std::get<int>(v1.get()->GetValue()), 1};
        }

        return this->expressionManager->AddConvertibleExpression(
            FractionExpression({value1.first * value2.second + value2.first * value1.second, value1.second * value2.second})
        );
    } else {
        return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
    }
}

std::weak_ptr<Expression> SimplifyRational::EvaluateProduct(const std::weak_ptr<Expression> u, const std::weak_ptr<Expression> v) {
    auto u1 = u.lock();
    auto v1 = v.lock();

    if (u1 && v1) {
        std::pair<int, int> value1, value2;

        if (u1.get()->GetType() == ExpressionType::FracOp) {
            value1 = std::get<std::pair<int, int>>(u1.get()->GetValue());
        } else {
            value1 = {std::get<int>(u1.get()->GetValue()), 1};
        }

        if (v1.get()->GetType() == ExpressionType::FracOp) {
            value2 = std::get<std::pair<int, int>>(v1.get()->GetValue());
        } else {
            value2 = {std::get<int>(v1.get()->GetValue()), 1};
        }

        return this->expressionManager->AddConvertibleExpression(
            FractionExpression({value1.first * value2.first, value1.second * value2.second})
        );
    } else {
        return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
    }
}

std::weak_ptr<Expression> SimplifyRational::EvaluatePower(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v) {
    auto u1 = u.lock();
    auto v1 = v.lock();

    //calculate u ^ v
    if (u1 && v1) {
        if (v1.get()->GetType() != ExpressionType::Integer) {
            return this->expressionManager->AddConvertibleExpression(UndefinedExpression()); //we don't deal with roots here
        }

        int up = std::get<int>(v1.get()->GetValue());

        std::pair<int, int> val;
        if (u1.get()->GetType() == ExpressionType::FracOp) {
            val = std::get<std::pair<int, int>>(u1.get()->GetValue());
        } else {
            val = {std::get<int>(u1.get()->GetValue()), 1};
        }

        if (val.first == 0) {
            if (up >= 1) {
                return this->expressionManager->AddConvertibleExpression(IntegerExpression(0)); //0 ^ x = 0
            } 
            else if (up <= 0) {
                return this->expressionManager->AddConvertibleExpression(UndefinedExpression()); //x / 0 = Undefined
            } 
        } 
        
        else {
            if (up > 0) {
                int nume = std::pow(val.first, up);
                int deno = std::pow(val.second, up);
                return this->expressionManager->AddConvertibleExpression(FractionExpression({nume, deno}));
            } else if (up == 0) {
                return this->expressionManager->AddConvertibleExpression(IntegerExpression(1)); //x ^ 0 = 1
            } else {
                int nume = std::pow(val.first, -up);
                int deno = std::pow(val.second, -up);
                return this->expressionManager->AddConvertibleExpression(FractionExpression({deno, nume})); // a ^ -b = 1 / (a^b)
            }
        }
    }

    return this->expressionManager->AddConvertibleExpression(UndefinedExpression());
}

//comparison functions down there! Careful!
int SimplifyRational::CompareRational(std::weak_ptr<Expression> u, std::weak_ptr<Expression> v) {
    auto u1 = u.lock();
    auto v1 = v.lock();

    if (u1 && v1) {
        std::pair<int, int> value1, value2;

        if (u1.get()->GetType() == ExpressionType::FracOp) {
            value1 = std::get<std::pair<int, int>>(u1.get()->GetValue());
        } else if (u1.get()->GetType() == ExpressionType::Integer) {
            value1 = {std::get<int>(u1.get()->GetValue()), 1};
        } else {
            throw std::invalid_argument("Compare type not Fraction or Integer!");
        }

        if (v1.get()->GetType() == ExpressionType::FracOp) {
            value2 = std::get<std::pair<int, int>>(v1.get()->GetValue());
        } else if (v1.get()->GetType() == ExpressionType::Integer) {
            value2 = {std::get<int>(v1.get()->GetValue()), 1};
        } else {
            throw std::invalid_argument("Compare type not Fraction or Integer!");
        }

        int comper = (value1.first * value2.second - value2.first * value1.second);
        if (comper < 0) {return -1;} //u1 < v1
        else if (comper > 0) {return 1;} //u1 > v1
        else {return 0;} //u1 = v1
    }

    std::cerr << "Compare failed!\n";
    return -1;
}

//unsafe for a CAS - but it works ¯\_(ツ)_/¯ 
//probably use for integer comparison mostly. Pray god it works
int SimplifyRational::CompareRational(std::weak_ptr<Expression> u, float val) {
    auto u1 = u.lock();
    if (u1) {
        std::pair<int, int> value1;

        if (u1.get()->GetType() == ExpressionType::FracOp) {
            value1 = std::get<std::pair<int, int>>(u1.get()->GetValue());
        } else if (u1.get()->GetType() == ExpressionType::Integer) {
            value1 = {std::get<int>(u1.get()->GetValue()), 1};
        } else {
            throw std::invalid_argument("Compare type not Fraction or Integer!");
        }

        float other = (float) value1.first / value1.second;

        if (std::abs(other - val) <= this->exp) {return 0;} //u = val
        else if (other < val) {return -1;} //u < val
        else {return 1;} //u > val
    }

    std::cerr << "Compare failed!\n";
    return -1;
}