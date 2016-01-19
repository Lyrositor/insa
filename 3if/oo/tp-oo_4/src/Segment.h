#ifndef SEGMENT_H
#define SEGMENT_H

#include <string>
#include <istream>

#include "Polygon.h"
#include "Vector2D.h"

class Segment : public Polygon
{
public:
    Segment(Vector2D point1, Vector2D point2);
    
    char getType()
    {
        return SEGMENT;
    }
    bool contains(Vector2D point);
    std::string serialize();
    static Segment unserialize(std::istream is)
    {
        long x, y;
        char c;
        is >> x >> c >> y;
        Vector2D a(x, y);
        is >> x >> c >> y;
        Vector2D b(x, y);
        
        return Segment(a, b);
    }
};

#endif // SEGMENT_H
