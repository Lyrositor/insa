#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <istream>
#include <ostream>
#include <string>

#include "Polygon.h"
#include "Vector2D.h"

class Rectangle : public Polygon
{
public:
    Rectangle(const Vector2D& point1, const Vector2D& point2) :
            Polygon({point1, point2}) {};

    bool contains(const Vector2D& point) const;
    Figure* createCopy() const;
    char getType() const { return RECTANGLE; }

    friend std::ostream& operator<<(std::ostream& os, const Rectangle* rect);
    friend std::istream& operator>>(std::istream& is, Rectangle*& rect);
};

#endif // RECTANGLE_H
