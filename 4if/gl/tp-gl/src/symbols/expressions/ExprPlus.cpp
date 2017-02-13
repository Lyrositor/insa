#include "ExprPlus.h"

double ExprPlus::eval ()
{
    return left->eval() + right->eval();
}
