#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include <istream>
#include <ostream>
#include <vector>

#include "Polygon.h"
#include "Vector2D.h"

class ConvexPolygon : public Polygon
{
public:
    ConvexPolygon(const std::vector<Vector2D>& _points) : Polygon(_points) {};

    bool contains(const Vector2D& point) const;
    char getType() const { return CONVEX_POLYGON; };

    friend std::ostream& operator<<(std::ostream& os, const ConvexPolygon* cp);
    friend std::istream& operator>>(std::istream& is, ConvexPolygon*& cp);
};

#endif // CONVEX_POLYGON_H
