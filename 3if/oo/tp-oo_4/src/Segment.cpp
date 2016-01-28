#include <cmath>

#include "Segment.h"

bool Segment::contains(const Vector2D& point) const
{
    float AB = sqrt((points[1].x - points[0].x) * (points[1].x - points[0].x) + (points[1].y - points[0].y) * (points[1].y - points[0].y));
    float AP = sqrt((point.x - points[0].x) * (point.x - points[0].x) + (point.y - points[0].y) * (point.y - points[0].y));
    float PB = sqrt((points[1].x - point.x) * (points[1].x - point.x) + (points[1].y - point.y) * (points[1].y - point.y));
    return AB == AP + PB;
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
