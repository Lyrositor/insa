#ifndef NUMBER_H
#define NUMBER_H

#include "../../Expression.h"

class Number : public Expression
{
public:
    Number (int val) : Expression(), value(val) {}
    virtual double eval ();

protected:
    int value;
};

#endif // EXPR_BIN_H
