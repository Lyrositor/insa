#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <stack>

#include "Symbol.h"


class Lexer
{
public:
    Lexer (std::string & expr) : head(0), expression(expr) {};
    Symbol * next ();
    void pushSymbol (Symbol * symbol);

protected:
    std::string::size_type head;
    std::string expression;
    std::stack<Symbol *> buffer;
};


#endif // LEXER_H
