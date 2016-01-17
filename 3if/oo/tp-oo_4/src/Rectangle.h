#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Polygon.h"
#include "Vector2D.h"

class Rectangle : public Polygon
{
public:
    Rectangle(Vector2D _point1, Vector2D _point2) : point1(_point1), point2(_point2) {}
    
private:
    Vector2D point1;
    Vector2D point2;
};

#endif // RECTANGLE_H
