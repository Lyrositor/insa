#include "lexer.h"

#include "exceptions.h"
#include "tokens.h"

Lexer::~Lexer ()
{
    // Clear any tokens still left in the buffer
    while (!buffer.empty())
    {
        delete buffer.top();
        buffer.pop();
    }
}

Token * Lexer::next ()
{
    // If tokens were inserted by the parser, return the latest one first
    if (!buffer.empty())
    {
        Token * token = buffer.top();
        buffer.pop();
        return token;
    }

    // Check if we have reached the end or gone past it
    if (head > expression.size())
    {
        throw GlException("Reading past end");
    }
    else if (head == expression.size())
    {
        return new End;
    }

    Token * token;
    char c = expression[head];
    if (isdigit(c))
    {
        // Build the number token
        int number = c - '0';
        head++;
        while ((c = expression[head]) && isdigit(c))
        {
            number *= 10;
            number += c - '0';
            head++;
        }
        token = new Number(number);
    }
    else
    {
        // Build a single-character token
        switch (c) {
            case '+':
                token = new Plus;
                break;
            case '*':
                token = new Mult;
                break;
            case '(':
                token = new ParOpen;
                break;
            case ')':
                token = new ParClose;
                break;
            default:
                throw GlException("Invalid character: " + c);
        }
        head++;
    }

    return token;
}

void Lexer::pushToken (Token * token)
{
    buffer.push(token);
}
