#include "tokens.h"

double ExprNumber::eval ()
{
    return value;
}

double ExprMult::eval ()
{
    return left->eval() * right->eval();
}

double ExprPlus::eval ()
{
    return left->eval() + right->eval();
}
