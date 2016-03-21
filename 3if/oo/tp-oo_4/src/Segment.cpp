#include <cmath>

#include "Segment.h"

Segment::Segment(const Vector2D& point1, const Vector2D& point2)
{
    points = {point1, point2};
}

bool Segment::contains(const Vector2D& point) const
{
    // Check firstly if the points are aligned through the cross product of
    // AP = points[0] -> point and AB = point[0] -> points[1].
    // Then, make sure the scalar product of AP and AB is between 0 (point is
    // on points[0]) and the scalar product of AB and AB (point is on
    // points[1]).
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
