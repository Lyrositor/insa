#ifndef EXPR_NUMBER_H
#define EXPR_NUMBER_H

#include "../../Expression.h"

class ExprNumber : public Expression
{
public:
    ExprNumber (int val) : Expression(), value(val) {}
    virtual double eval ();

protected:
    int value;
};

#endif // EXPR_NUMBER_H
