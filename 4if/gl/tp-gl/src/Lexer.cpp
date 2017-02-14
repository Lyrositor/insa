#include <stdexcept>

#include "Lexer.h"
#include "symbols/End.h"
#include "symbols/Mult.h"
#include "symbols/Number.h"
#include "symbols/ParClose.h"
#include "symbols/ParOpen.h"
#include "symbols/Plus.h"
#include "symbols/expressions/ExprNumber.h"

Lexer::Lexer (std::string & expression) : head(0)
{
    lex(expression);
}

Lexer::~Lexer ()
{
    for (Symbol * symbol : symbols)
    {
        delete symbol;
    }
}

Symbol * Lexer::getNext ()
{
    if (head < symbols.size())
    {
        return symbols[head++];
    }
    return nullptr;
}

void Lexer::lex (std::string & expression)
{
    std::string number;
    for (char& c : expression)
    {
        Symbol * symbol;
        if (c - '0' >= 0 && '9' - c >= 0)
        {
            number += c;
            continue;
        }

        if (!number.empty())
        {
            symbols.push_back(new Number(atoi(number.c_str())));
            number.clear();
        }
        switch (c) {
            case '+':
                symbol = new Plus;
                break;
            case '*':
                symbol = new Mult;
                break;
            case '(':
                symbol = new ParOpen;
                break;
            case ')':
                symbol = new ParClose;
                break;
            default:
                throw std::invalid_argument("Invalid character: " + c);
        }

        symbols.push_back(symbol);
    }
    if (!number.empty())
    {
        symbols.push_back(new ExprNumber(atoi(number.c_str())));
    }
    symbols.push_back(new End);
}

void Lexer::seekBack ()
{
    if (head > 0)
    {
        head--;
    }
}
