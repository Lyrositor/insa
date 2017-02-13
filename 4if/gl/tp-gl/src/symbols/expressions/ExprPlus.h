#ifndef EXPR_PLUS_H
#define EXPR_PLUS_H

#include "ExprBin.h"

class ExprPlus : public ExprBin
{
public:
    ExprPlus (Expression * l, Expression * r) : ExprBin(l, r) {}
    virtual double eval ();
};

#endif // EXPR_PLUS_H
