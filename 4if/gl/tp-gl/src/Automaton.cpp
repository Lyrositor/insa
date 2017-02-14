#include <stdexcept>

#include "Automaton.h"
#include "State.h"
#include "Symbol.h"
#include "States.h"

int Automaton::parse (std::string & expression)
{
    lexer = new Lexer(expression);
    states.push(new E0);

    State * state;
    Symbol * symbol;
    do {
        state = states.top();
        symbol = lexer->getNext();
        if (symbol == nullptr)
        {
            throw std::runtime_error("Read past end symbol.");
        }
    } while (!state->transition(*this, symbol));

    if (symbols.size() != 1)
    {
        delete lexer;
        throw std::length_error("Symbols stack should be of size one.");
    }
    int evaluation = static_cast<int>(
            static_cast<Expression *>(symbols.top())->eval()
    );

    while (!symbols.empty())
    {
        symbols.pop();
    }
    while (!states.empty())
    {
        states.pop();
    }
    delete lexer;

    return evaluation;
}

Symbol * Automaton::pop ()
{
    Symbol * symbol = symbols.top();
    symbols.pop();
    return symbol;
}

void Automaton::popAndDestroy ()
{
    delete symbols.top();
    symbols.pop();
}

void Automaton::shift (Symbol * symbol, State * state)
{
    symbols.push(symbol);
    states.push(state);
}

void Automaton::reduce (unsigned int n, Symbol * s)
{
    for (unsigned int i = 0; i < n; i++)
    {
        delete states.top();
        states.pop();
    }
    lexer->seekBack();
    states.top()->transition(*this, s);
}
