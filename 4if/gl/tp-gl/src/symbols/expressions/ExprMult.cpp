#include "ExprMult.h"

double ExprMult::eval ()
{
    return left->eval() * right->eval();
}
