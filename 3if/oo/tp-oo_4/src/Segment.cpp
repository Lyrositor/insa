#include <cmath>

#include "Segment.h"

bool Segment::contains(const Vector2D& point) const
{
    Vector2D AB = points[1].sub(points[0]);
    Vector2D AP = point.sub(points[0]);
    long scalar = AB.scalar(AP);
    return AB.cross(AP) == 0 && scalar >= 0 && scalar <= AB.scalar(AB);
}

Figure* Segment::createCopy() const {
    return new Segment(*this);
}

std::ostream& operator<<(std::ostream& os, const Segment* segment)
{
    return segment->serializePoints(os);
}

std::istream& operator>>(std::istream& is, Segment*& segment)
{
    std::vector<Vector2D> points = Polygon::unserializePoints(is);
    segment = new Segment(points[0], points[1]);
    return is;
}
