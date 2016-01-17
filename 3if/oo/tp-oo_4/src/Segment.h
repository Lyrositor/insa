#ifndef SEGMENT_H
#define SEGMENT_H

#include "Polygon.h"
#include "Vector2D.h"

class Segment : public Polygon
{
public:
    Segment(Vector2D _point1, Vector2D _point2): point1(_point1), point2(_point2) {}
    
private:
    Vector2D point1;
    Vector2D point2;
};

#endif // SEGMENT_H
