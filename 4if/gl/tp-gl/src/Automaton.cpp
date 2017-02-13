#include <stdexcept>

#include "Automaton.h"
#include "State.h"
#include "Symbol.h"
#include "States.h"

int Automaton::parse (std::string & expression)
{
    lexer = new Lexer(expression);
    State * state = new E0;
    state->transition(*this, lexer->getNext());
    if (symbols.size() != 1)
    {
        delete lexer;
        throw std::length_error("Symbols stack should be of size one.");
    }
    int evaluation = static_cast<int>(
            static_cast<Expression *>(symbols.top())->eval()
    );

    delete lexer;
    while (!symbols.empty())
    {
        symbols.pop();
    }
    while (!states.empty())
    {
        states.pop();
    }

    return evaluation;
}

void Automaton::shift (Symbol * symbol, State * state)
{
    symbols.push(symbol);
    states.push(state);
    // TODO Consume symbol (head++)
}

void Automaton::reduce (unsigned int n, Symbol * s)
{
    for (unsigned int i = 0; i < n; i++)
    {
        delete states.top();
        states.pop();
    }
    states.top()->transition(*this, s);
}
