#ifndef FIGURE_H
#define FIGURE_H

#include <istream>
#include <ostream>

#include "Vector2D.h"

class Figure
{
public:
    static const char CONVEX_POLYGON = 'C';
    static const char INTERSECTION = 'I';
    static const char RECTANGLE = 'R';
    static const char SEGMENT = 'S';
    static const char UNION = 'U';

    virtual ~Figure() {}

    template<class T> const T* as() const
    {
        return static_cast<const T*>(this);
    }
    Figure* createCopy() const;
    virtual char getType() const = 0;

    virtual bool contains(const Vector2D& point) const = 0;
    virtual void move(const Vector2D& delta) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure* figure);
    friend std::istream& operator>>(std::istream& is, Figure*& figure);
};

#endif // FIGURE_H
