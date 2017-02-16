#include <iostream>
#include "parser.h"

#include "exceptions.h"
#include "states.h"
#include "tokens.h"

Parser::~Parser ()
{
    while (!tokens.empty())
    {
        delete tokens.top();
        tokens.pop();
    }
    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}

int Parser::parse (std::string & expression)
{
    while (!tokens.empty())
    {
        delete tokens.top();
        tokens.pop();
    }
    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }

    lexer = new Lexer(expression);

    try
    {
        states.push(new E0);
        while (!states.top()->transition(*this, lexer->next()));
    } catch (const GlException & e) {
        delete lexer;
        throw e;
    }
    delete lexer;

    if (tokens.size() != 1)
    {
        throw GlException("Symbols stack should be of size one.");
    }
    int evaluation = static_cast<int>(
            static_cast<Expression *>(tokens.top())->eval()
    );

    return evaluation;
}

Token * Parser::pop ()
{
    Token * token = tokens.top();
    tokens.pop();
    return token;
}

void Parser::popAndDestroy ()
{
    delete tokens.top();
    tokens.pop();
}

void Parser::shift (Token * token, State * state)
{
    tokens.push(token);
    states.push(state);
}

void Parser::reduce (
        unsigned int n, Token * newToken, Token * unvisitedToken
)
{
    for (unsigned int i = 0; i < n; i++)
    {
        delete states.top();
        states.pop();
    }
    lexer->pushToken(unvisitedToken);
    states.top()->transition(*this, newToken);
}
