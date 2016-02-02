#include "ConvexPolygon.h"

bool ConvexPolygon::contains(const Vector2D& p) const
/* From:
    https://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html */
{
    bool result = false;

    for (size_t s = points.size(), i = 0, j = s - 1; i < s; j = i++)
    {
        if ((points[i].y > p.y) != (points[j].y > p.y) &&
            (p.x < (points[j].x - points[i].x) * (p.y - points[i].y) /
                           (points[j].y-points[i].y) + points[i].x))
            {
                result = !result;
            }
    }

    return result;
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
