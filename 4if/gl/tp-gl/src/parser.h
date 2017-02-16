#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <stack>

#include "lexer.h"
#include "state.h"

/**
 * Utility for interpreting strings as mathematical expressions.
 *
 * A valid expression here consists only of plus signs, multiplication signs,
 * parentheses and numbers.
 */
class Parser
{
public:
    /**
     * Destructs the parser.
     */
    ~Parser ();

    /**
     * Parses a string as a mathematical expression.
     *
     * @param expression The string to interpret as an expression.
     * @return
     */
    int parse (std::string & expression);

    /**
     * Pops and returns the last parsed token.
     *
     * @return The popped token.
     */
    Token * pop ();

    /**
     * Pops and destroys the last parsed token.
     */
    void popAndDestroy ();

    /**
     * Performs a reduction transition to the left.
     *
     * @param n The amount of states to undo.
     * @param newToken The new token to insert.
     * @param unvisitedToken The token which triggered this reduction.
     */
    void reduce (unsigned int n, Token * newToken, Token * unvisitedToken);

    /**
     * Performs a shift transition to the right.
     *
     * @param token The token to add.
     * @param state The state to add.
     */
    void shift (Token * token, State * state);

protected:
    Lexer * lexer;
    std::stack<State *> states;
    std::stack<Token *> tokens;
};

#endif // PARSER_H
