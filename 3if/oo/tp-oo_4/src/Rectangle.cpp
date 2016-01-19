#include "Rectangle.h"

Rectangle::Rectangle(Vector2D point1, Vector2D point2)
{
    points.push_back(point1);
    points.push_back(point2);
}

long triangleArea(const Vector2D& a, const Vector2D& b, const Vector2D& c)
{
    return (c.x*b.y - b.x*c.y) - (c.x*a.y - a.x*c.y) + (b.x*a.y - a.x*b.y);
}

bool Rectangle::contains(Vector2D point)
{
    if (triangleArea(points[0],points[1],point) > 0 ||
        triangleArea(points[1],points[2],point) > 0 ||
        triangleArea(points[2],points[3],point) > 0 ||
        triangleArea(points[3],points[0],point) > 0)
    {
        return false;
    }
    return true;
}

std::string Rectangle::serialize()
{
    return std::string(1, getType()) + ' ' + serializePoints();
}