#include "ConvexPolygon.h"
#include "Segment.h"

bool ConvexPolygon::contains(const Vector2D& point) const
{
    // Make sure the point is always on the same side of the polygon's sides.
    // Since it's a convex polygon, if it's on the other side even once, the
    // point is located outside of the polygon.
    long lastCross = 0;
    for (size_t i = 0, s = points.size(); i < s; i++)
    {
        Vector2D side = points[(i+1) % s].sub(points[i]);
        Vector2D toPoint = point.sub(points[i]);
        long cross = side.cross(toPoint);
        if (cross * lastCross <= 0 && lastCross != 0)
            return Segment(points[i], points[(i+1) % s]).contains(point);
        lastCross = cross;
    }

    return true;
}

Figure* ConvexPolygon::createCopy() const {
    return new ConvexPolygon(*this);
}

std::ostream& operator<<(std::ostream& os, const ConvexPolygon* cp)
{
    return cp->serializePoints(os);
}

std::istream& operator>>(std::istream& is, ConvexPolygon*& cp)
{
    cp = new ConvexPolygon(Polygon::unserializePoints(is));
    return is;
}
