#ifndef TOKENS_H
#define TOKENS_H

#include "lexer.h"
#include "token.h"

class Number : public Token
{
public:
    Number (int val) : Token(Token::NUMBER), value(val) {}

    int getValue () { return value; }

protected:
    int value;
};

class ParClose : public Token
{
public:
    ParClose () : Token(Token::PARCLOSE) {}
};

class ParOpen : public Token
{
public:
    ParOpen () : Token(Token::PAROPEN) {}
};

class Mult : public Token
{
public:
    Mult () : Token(Token::MULT) {}
};

class Plus : public Token
{
public:
    Plus () : Token(Token::PLUS) {}
};

class End : public Token
{
public:
    End () : Token(Token::END) {}
};

class Expression : public Token
{
public:
    Expression () : Token(EXPRESSION) {}
    virtual ~Expression () {}
    virtual double eval () = 0;
};

class ExprNumber : public Expression
{
public:
    ExprNumber (int val) : Expression(), value(val) {}
    virtual double eval ();

protected:
    int value;
};

class ExprBin : public Expression
{
public:
    ExprBin (Expression * l, Expression * r) : left(l), right(r) {}
    virtual ~ExprBin () { delete left; delete right; }
    virtual double eval () = 0;

protected:
    Expression * left;
    Expression * right;
};

class ExprMult : public ExprBin
{
public:
    ExprMult (Expression * l, Expression * r) : ExprBin(l, r) {}
    virtual double eval ();
};

class ExprPlus : public ExprBin
{
public:
    ExprPlus (Expression * l, Expression * r) : ExprBin(l, r) {}
    virtual double eval ();
};

#endif // TOKENS_H
