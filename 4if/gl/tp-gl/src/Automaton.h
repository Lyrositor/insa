#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <string>
#include <stack>

#include "Expression.h"
#include "Lexer.h"

class Symbol;
class State;

class Automaton
{
public:
    int parse (std::string & expression);
    Symbol * pop ();
    void popAndDestroy ();
    void reduce (unsigned int n, Symbol * s);
    void shift (Symbol * symbol, State * state);

protected:
    Lexer * lexer;
    std::stack<State *> states;
    std::stack<Symbol *> symbols;
};


#endif // LRPARSER_H
