#ifndef SYMBOL_H
#define SYMBOL_H

class Symbol
{
public:
    enum Type {
        END,
        EXPRESSION,
        MULT,
        NUMBER,
        PARCLOSE,
        PAROPEN,
        PLUS
    };

    Symbol (Type id) : ident(id) {}
    virtual ~Symbol () {}
    void print () const;
    operator int () const { return ident; }

protected:
    Type ident;
};


#endif // SYMBOL_H
