#include "states.h"

#include "exceptions.h"
#include "tokens.h"

bool E0::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::NUMBER:
            parser.shift(token, new E3);
            break;
        case Token::PAROPEN:
            parser.shift(token, new E2);
            break;
        case Token::EXPRESSION:
            parser.shift(token, new E1);
            break;
        default:
            delete token;
            throw GlException("Invalid token for E0");
    }
    return false;
}

bool E1::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::PLUS:
            parser.shift(token, new E4);
            break;
        case Token::MULT:
            parser.shift(token, new E5);
            break;
        case Token::END:
            delete token;
            return true;
        default:
            delete token;
            throw GlException("Invalid token for E1");
    }
    return false;
}

bool E2::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::NUMBER:
            parser.shift(token, new E3);
            break;
        case Token::PAROPEN:
            parser.shift(token, new E2);
            break;
        case Token::EXPRESSION:
            parser.shift(token, new E6);
            break;
        default:
            delete token;
            throw GlException("Invalid token for E2");
    }
    return false;
}

bool E3::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::PLUS:
        case Token::MULT:
        case Token::PARCLOSE:
        case Token::END:
        {
            Number * number = static_cast<Number *>(parser.pop());
            parser.reduce(1, new ExprNumber(number->getValue()), token);
            delete number;
            break;
        }
        default:
            delete token;
            throw GlException("Invalid token for E3");
    }
    return false;
}

bool E4::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::NUMBER:
            parser.shift(token, new E3);
            break;
        case Token::PAROPEN:
            parser.shift(token, new E2);
            break;
        case Token::EXPRESSION:
            parser.shift(token, new E7);
            break;
        default:
            delete token;
            throw GlException("Invalid token for E4");
    }
    return false;
}

bool E5::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::NUMBER:
            parser.shift(token, new E3);
            break;
        case Token::PAROPEN:
            parser.shift(token, new E2);
            break;
        case Token::EXPRESSION:
            parser.shift(token, new E8);
            break;
        default:
            delete token;
            throw GlException("Invalid token for E5");
    }
    return false;
}

bool E6::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::MULT:
            parser.shift(token, new E5);
            break;
        case Token::PLUS:
            parser.shift(token, new E4);
            break;
        case Token::PARCLOSE:
            parser.shift(token, new E9);
            break;
        default:
            delete token;
            throw GlException("Invalid token for E6");
    }
    return false;
}

bool E7::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::MULT:
            parser.shift(token, new E5);
            break;
        case Token::PLUS:
        case Token::PARCLOSE:
        case Token::END:
        {
            ExprNumber * left = static_cast<ExprNumber *>(parser.pop());
            Token * opToken = parser.pop();
            int op = static_cast<int>(*opToken);
            delete opToken;
            ExprNumber * right = static_cast<ExprNumber *>(parser.pop());
            if (op == Token::PLUS)
            {
                parser.reduce(3, new ExprPlus(left, right), token);
            }
            else if (op == Token::MULT)
            {
                parser.reduce(3, new ExprMult(left, right), token);
            }
            else
            {
                delete token;
                throw GlException("Unexpected operator");
            }
            break;
        }
        default:
            delete token;
            throw GlException("Invalid token for E7");
    }
    return false;
}

bool E8::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::MULT:
        case Token::PLUS:
        case Token::PARCLOSE:
        case Token::END:
        {
            ExprNumber * left = static_cast<ExprNumber *>(parser.pop());
            Token * opToken = parser.pop();
            int op = static_cast<int>(*opToken);
            delete opToken;
            ExprNumber * right = static_cast<ExprNumber *>(parser.pop());
            if (op == Token::PLUS)
            {
                parser.reduce(3, new ExprPlus(left, right), token);
            }
            else if (op == Token::MULT)
            {
                parser.reduce(3, new ExprMult(left, right), token);
            }
            else
            {
                throw GlException("Unexpected operator");
            }
            break;
        }
        default:
            throw GlException("Invalid token for E8");

    }
    return false;
}

bool E9::transition(Parser & parser, Token * token) {
    switch (*token) {
        case Token::MULT:
        case Token::PLUS:
        case Token::PARCLOSE:
        case Token::END:
        {
            parser.popAndDestroy();
            Expression * expression = static_cast<Expression *>(parser.pop());
            parser.popAndDestroy();
            parser.reduce(3, expression, token);
            break;
        }
        default:
            delete token;
            throw GlException("Invalid token for E9");

    }
    return false;
}
