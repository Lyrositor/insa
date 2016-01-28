#include "Rectangle.h"

long triangleArea(const Vector2D& a, const Vector2D& b, const Vector2D& c)
{
    return (c.x*b.y - b.x*c.y) - (c.x*a.y - a.x*c.y) + (b.x*a.y - a.x*b.y);
}

bool Rectangle::contains(const Vector2D& point) const
{
    return !(
            triangleArea(points[0], points[1], point) > 0 ||
            triangleArea(points[1], points[2], point) > 0 ||
            triangleArea(points[2], points[3], point) > 0 ||
            triangleArea(points[3], points[0], point) > 0
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
