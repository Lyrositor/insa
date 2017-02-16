#ifndef STATES_H
#define STATES_H

#include "parser.h"
#include "state.h"

class E0 : public State
{
public:
    E0 () : State("E0") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E1 : public State
{
public:
    E1 () : State("E1") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E2 : public State
{
public:
    E2 () : State("E2") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E3 : public State
{
public:
    E3 () : State("E3") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E4 : public State
{
public:
    E4 () : State("E4") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E5 : public State
{
public:
    E5 () : State("E5") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E6 : public State
{
public:
    E6 () : State("E6") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E7 : public State
{
public:
    E7 () : State("E7") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E8 : public State
{
public:
    E8 () : State("E8") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

class E9 : public State
{
public:
    E9 () : State("E9") {}
    virtual bool transition (Parser & parser, Token * symbol);
};

#endif // STATES_H
