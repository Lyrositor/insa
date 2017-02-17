#ifndef STATE_H
#define STATE_H

#include <string>

#include "token.h"

class Parser;

/**
 * A state in the parser's automaton.
 */
class State
{
public:
    /**
     * Constructs a named state.
     *
     * @param stateName The name of the state, for debugging purposes.
     */
    State (std::string stateName) : name(stateName) {}

    /**
     * Destructs the state.
     */
    virtual ~State() {}

    /**
     * Executes the appropriate transition from this state to the next.
     *
     * @param parser The parser automaton to use for the transition.
     * @param token The token that is being consumed.
     * @return true if the end has been reached, false otherwise.
     */
    virtual bool transition (Parser & parser, Token * token) = 0;

protected:
    std::string name;
};

#endif // STATE_H
