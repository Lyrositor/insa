#ifndef STATE_H
#define STATE_H

#include "Symbol.h"

class Automaton;

class State
{
public:
    State (std::string stateName) : name(stateName) {}
    virtual ~State () {}
    void print () const;
    virtual bool transition (Automaton & automaton, Symbol * symbol) = 0;

protected:
    std::string name;
};


#endif // STATE_H
