#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "Symbol.h"


class Lexer
{
public:
    Lexer(std::string & expression);
    ~Lexer();
    void lex (std::string & expression);
    Symbol * getNext();

protected:
    std::vector<Symbol *>::size_type head;
    std::vector<Symbol *> symbols;
};


#endif // LEXER_H
