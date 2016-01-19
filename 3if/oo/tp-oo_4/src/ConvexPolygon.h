#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include <vector>
#include <istream>

#include "Polygon.h"
#include "Vector2D.h"

class ConvexPolygon : public Polygon
{
public:
    ConvexPolygon(std::vector<Vector2D> _points);
    
    void appendPoint(const Vector2D& point);
    char getType()
    {
        return CONVEX_POLYGON;
    }
    bool contains(Vector2D point);
    std::string serialize();
    static ConvexPolygon unserialize(std::istream is)
    {
        long x, y;
        char c;
        std::vector<Vector2D> points;
        while(is)
        {
            is >> x >> c >> y;
            Vector2D p(x, y);
            points.push_back(p);
        }
        
        return ConvexPolygon(points);
    }
};

#endif // CONVEX_POLYGON_H
