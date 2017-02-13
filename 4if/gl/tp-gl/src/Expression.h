#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

#include "Symbol.h"

class Expression : public Symbol
{
public:
    Expression () : Symbol(EXPRESSION) {}
    virtual ~Expression () {}
    virtual double eval () = 0;
};


#endif // EXPRESSION_H
