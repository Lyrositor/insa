#ifndef TOKEN_H
#define TOKEN_H

class Token
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

    Token (Type id) : ident(id) {}
    virtual ~Token () {}
    operator int () const { return ident; }

protected:
    Type ident;
};

#endif // TOKEN_H
