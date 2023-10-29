#include "astparser.h"

void ASTParser::Initialize(sf::RenderWindow* window, Lexer* lex) {
    this->window = window;
    this->lex = lex;

    this->nodes.reserve(100000);
}

void ASTParser::Update(sf::Event event) {
}

void ASTParser::Visualize(sf::Event event) {

}

void ASTParser::LateUpdate() {

}

void ASTParser::Reset() {
    this->nodes.clear();
    this->nodes.reserve(100000);
}

int ASTParser::GetPrecedence(Token token) {
    if (this->precedence.find(token.value) == this->precedence.end()) {
        return 0;
    }

    return this->precedence[token.value];
}

void ASTParser::Debug(ASTNode* root, int level) {
    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    std::cout << root->value << '\n';
    for (auto child: root->children) {
        this->Debug(child, level + 1);
    }
}

ASTNode* ASTParser::Parse(std::string input) {
    this->lex->InitiateInput(input);
    ASTNode* output = this->Expression(0);
    return output;
}

ASTNode* ASTParser::Expression(int curPrecedence) {
    ASTNode* lhs = this->PrefixHandler();

    while (curPrecedence < this->GetPrecedence(this->lex->GetCurrentToken())) {
        lhs = this->InfixHandler(lhs, this->lex->GetCurrentToken().type);
    }

    return lhs;
}

ASTNode* ASTParser::InfixHandler(ASTNode* lhs, TokenType type) {
    Token curToken = this->lex->GetCurrentToken();
    this->lex->Eat(type);

    int newPrec = this->GetPrecedence(curToken);
    if (type == TokenType::ADDITION) {
        ASTNode tmp("<Binary operator +>"); 
        
        ASTNode* par = this->AddNewNode(tmp);
        ASTNode* rhs = this->Expression(newPrec);
        
        par->AddChild(lhs); par->AddChild(rhs);
        return par;
    } else if (type == TokenType::MULTIPLICATION) {
        ASTNode tmp("<Binary operator *>"); 
        
        ASTNode* par = this->AddNewNode(tmp);
        ASTNode* rhs = this->Expression(newPrec);

        par->AddChild(lhs); par->AddChild(rhs);
        return par;
    } else if (type == TokenType::SUBTRACTION) {
        ASTNode tmp("<Binary operator ->"); 
        
        ASTNode* par = this->AddNewNode(tmp);
        ASTNode* rhs = this->Expression(newPrec);

        par->AddChild(lhs); par->AddChild(rhs);
        return par;
    } else if (type == TokenType::DIVISION) {
        ASTNode tmp("<Binary operator />"); 
        
        ASTNode* par = this->AddNewNode(tmp);
        ASTNode* rhs = this->Expression(newPrec);

        par->AddChild(lhs); par->AddChild(rhs);
        return par;
    } else if (type == TokenType::EXPONENTIATION) {
        ASTNode tmp("<Binary operator ^>"); 
        
        ASTNode* par = this->AddNewNode(tmp);
        ASTNode* rhs = this->Expression(newPrec - 1);

        par->AddChild(lhs); par->AddChild(rhs);
        return par;

        //power rule follows right hand first
        //for example, 2^3^5 should be evaluated as 2^(3^5), not (2^3)^5 like addition or multiplication
    }

    throw std::invalid_argument("Undefined operators/number detected: Infix");
}

ASTNode* ASTParser::PrefixHandler() {
    ASTFunc trigHandler = this->TrigPrefixHandler();
    if (trigHandler.matched) {
        return trigHandler.value;
    }

    Token curToken = this->lex->GetCurrentToken();

    if (curToken.type == TokenType::SUBTRACTION) {
        curToken.value = "unary";
        this->lex->Eat(TokenType::SUBTRACTION);

        ASTNode tmp("<Unary operator ->"); ASTNode* par = this->AddNewNode(tmp);
        ASTNode* rhs = this->Expression(this->GetPrecedence(curToken));

        par->AddChild(rhs);
        return par;
    }

    if (curToken.type == TokenType::ADDITION) {
        curToken.value = "unary";
        this->lex->Eat(TokenType::ADDITION);

        ASTNode tmp("<Unary operator +>"); ASTNode* par = this->AddNewNode(tmp);
        ASTNode* rhs = this->Expression(this->GetPrecedence(curToken));

        par->AddChild(rhs);
        return par;
    }
    
    if (curToken.type == TokenType::LEFT_PARENTHESIS) {
        this->lex->Eat(TokenType::LEFT_PARENTHESIS);
        ASTNode* exp = this->Expression(0);
        this->lex->Eat(TokenType::RIGHT_PARENTHESIS);
 
        return exp;
    }

    //only case left is number
    this->lex->Eat(TokenType::NUMBER);

    ASTNode tmp("<Number " + curToken.value + ">"); ASTNode* val = this->AddNewNode(tmp);
    return val;
}

ASTFunc ASTParser::TrigPrefixHandler() {
    Token curToken = this->lex->GetCurrentToken();
    switch(curToken.type) {
        case TokenType::SINE: {
            this->lex->Eat(curToken.type);

            ASTNode tmp("<Function " + curToken.value + ">"); ASTNode* par = this->AddNewNode(tmp);
            par->AddChild(this->CurlyParenthesisHandler());

            return {true, par};
            break;
        } 
        case TokenType::COSINE: {
            this->lex->Eat(curToken.type);
            
            ASTNode tmp("<Function " + curToken.value + ">"); ASTNode* par = this->AddNewNode(tmp);
            par->AddChild(this->CurlyParenthesisHandler());

            return {true, par};
            break;
        } 
        case TokenType::TANGENT: {
            this->lex->Eat(curToken.type);
            
            ASTNode tmp("<Function " + curToken.value + ">"); ASTNode* par = this->AddNewNode(tmp);
            par->AddChild(this->CurlyParenthesisHandler());

            return {true, par};
            break;
        } 
        case TokenType::COTANGENT: {
            this->lex->Eat(curToken.type);
            
            ASTNode tmp("<Function " + curToken.value + ">"); ASTNode* par = this->AddNewNode(tmp);
            par->AddChild(this->CurlyParenthesisHandler());

            return {true, par};
            break;
        } 
        default: {
            return {false, nullptr};
        }
    }
}

ASTNode* ASTParser::CurlyParenthesisHandler() {
    this->lex->Eat(TokenType::LEFT_CURLY_PARENTHESIS);
    ASTNode* exp = this->Expression(0);
    this->lex->Eat(TokenType::RIGHT_CURLY_PARENTHESIS);

    return exp;
}