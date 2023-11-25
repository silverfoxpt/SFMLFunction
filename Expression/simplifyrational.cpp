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