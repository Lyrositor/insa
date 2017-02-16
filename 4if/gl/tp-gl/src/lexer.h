#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <stack>

#include "token.h"

/**
 * Lexer for the specified grammar.
 *
 * This lexer breaks down a string into a sequence of tokens that can then be
 * parsed.
 */
class Lexer
{
public:
    /**
     * Constructs a new lexer from the provided expression.
     *
     * @param expr The expression to lex.
     */
    Lexer (std::string & expr) : head(0), expression(expr) {};

    /**
     * Destructs the lexer.
     */
    ~Lexer ();

    /**
     * Returns the next token in the expression if available.
     *
     * If the end has been reached, the special END token is returned.
     * @return The next token.
     */
    Token * next ();

    /**
     * Pushes a new token to the front of the lexer.
     *
     * The token will be consumed before any other unread token the next time
     * next() is called.
     * @param token
     */
    void pushToken (Token * token);

protected:
    std::string::size_type head;
    std::string expression;
    std::stack<Token *> buffer;
};

#endif // LEXER_H
