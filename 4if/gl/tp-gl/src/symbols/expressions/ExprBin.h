#ifndef EXPR_BIN_H
#define EXPR_BIN_H

#include "../../Expression.h"

class ExprBin : public Expression
{
public:
    ExprBin (Expression * l, Expression * r);
    virtual double eval () = 0;

protected:
    Expression * left;
    Expression * right;
};

#endif // EXPR_BIN_H
