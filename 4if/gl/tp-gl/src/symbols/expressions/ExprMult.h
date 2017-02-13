#ifndef EXPR_MULT_H
#define EXPR_MULT_H

#include "ExprBin.h"

class ExprMult : public ExprBin
{
public:
    ExprMult (Expression * l, Expression * r) : ExprBin(l, r) {}
    virtual double eval ();
};

#endif // EXPR_MULT_H
