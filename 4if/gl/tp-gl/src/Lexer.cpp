#include <stdexcept>

#include "Lexer.h"
#include "symbols/End.h"
#include "symbols/Mult.h"
#include "symbols/Number.h"
#include "symbols/ParClose.h"
#include "symbols/ParOpen.h"
#include "symbols/Plus.h"

Symbol * Lexer::next ()
{
    if (!buffer.empty())
    {
        Symbol * symbol = buffer.top();
        buffer.pop();
        return symbol;
    }
    if (head > expression.size())
    {
        throw std::out_of_range("Reading past end");
    }
    else if (head == expression.size())
    {
        return new End;
    }

    Symbol * symbol;
    char c = expression[head];
    if (isdigit(c))
    {
        int number = c - '0';
        head++;
        while ((c = expression[head]) && isdigit(c))
        {
            number *= 10;
            number += c - '0';
            head++;
        }
        symbol = new Number(number);
    }
    else
    {
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
        head++;
    }

    return symbol;
}

void Lexer::pushSymbol (Symbol * symbol)
{
    buffer.push(symbol);
}
