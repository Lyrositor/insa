#ifndef NUMBER_H
#define NUMBER_H

class Number : public Symbol
{
public:
    Number (int val) : Symbol(Symbol::NUMBER), value(val) {}

    int getValue () { return value; }

protected:
    int value;
};

#endif // NUMBER_H
