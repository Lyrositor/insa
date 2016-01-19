#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <istream>

#include "Polygon.h"
#include "Vector2D.h"

class Rectangle : public Polygon
{
public:
    Rectangle(Vector2D point1, Vector2D point2);
    
    char getType()
    {
        return RECTANGLE;
    }
    bool contains(Vector2D point);
    std::string serialize();
    static Rectangle unserialize(std::istream is)
    {
        long x, y;
        char c;
        is >> x >> c >> y;
        Vector2D a(x, y);
        is >> x >> c >> y;
        Vector2D b(x, y);
        
        return Rectangle(a, b);
    }
};

#endif // RECTANGLE_H
