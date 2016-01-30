#include "Rectangle.h"

bool Rectangle::contains(const Vector2D& point) const
{
    return (
            (points[0].x <= point.x && point.x <= points[1].x) ||
            (points[1].x <= point.x && point.x <= points[0].x)
    ) && (
            (points[0].y <= point.y && point.y <= points[1].y) ||
            (points[1].y <= point.y && point.y <= points[0].y)
    );
}

std::ostream& operator<<(std::ostream& os, const Rectangle* rect)
{
    return rect->serializePoints(os);
}

std::istream& operator>>(std::istream& is, Rectangle*& rect)
{
    std::vector<Vector2D> points = Polygon::unserializePoints(is);
    rect = new Rectangle(points[0], points[1]);
    return is;
}
