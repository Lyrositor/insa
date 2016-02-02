#include <cmath>

#include "Segment.h"

bool Segment::contains(const Vector2D& point) const
{
    double AB = sqrt(
            pow(points[1].x-points[0].x, 2) + pow(points[1].y-points[0].y, 2)
    );
    double AP = sqrt(pow(point.x-points[0].x, 2) + pow(point.y-points[0].y, 2));
    double PB = sqrt(pow(point.x-points[1].x, 2) + pow(point.y-points[1].y, 2));
    return AB == AP + PB;
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
