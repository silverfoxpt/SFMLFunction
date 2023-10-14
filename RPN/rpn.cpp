#include "rpn.h"

void RPN::Initialize(sf::RenderWindow* window) {
    this->window = window;
}

void RPN::Update(sf::Event event) {
}

void RPN::Visualize(sf::Event event) {

}

void RPN::LateUpdate() {

}

void RPN::Reset() {

}

std::vector<std::string> RPN::InfixToPostfix(std::string infix) {
    //replace prefix function - TODO: IMPLEMENT

    //infix to postfix
    std::stack<opRpn> ops;
    std::vector<std::string> postfix;

    int i = 0;
    while (i < infix.size()) {
        //check for operator
        bool isOperator = false; opRpn myOp;
        for (auto op: this->operators) {
            if (StrHelp::matchAtPos(infix, i, op.op)) {
                isOperator = true;
                myOp = op;
                break;
            }
        }

        //if operator 
        if (isOperator) {
            //pop all previous operator with higher or equal precedence  
            while (ops.size() > 0) {
                opRpn nextOp = ops.top();
                if (nextOp.priority >= myOp.priority) {
                    ops.pop();                      //remove from operator stack
                    postfix.push_back(nextOp.op);   //push to postfix stack
                }
            }

            //push this operator to the stack
            ops.push(myOp);
        } else {
            //if number
            if (StrHelp::isNum(infix[i])) {
                //scrap the number into a string, make sure to take the decimal point as well
                std::string num = "";
                while (StrHelp::isNum(infix[i]) || infix[i] == '.') {
                    num += infix[i];
                    i++;
                }
                postfix.push_back(num);
            }

            //if opening bracket
            else if () {

            }

            //if variable
            else {
                std::string var = ""; var += infix[i];
                postfix.push_back(var);
            }
        }
    }

    return postfix;
}