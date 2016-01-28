#include "Polygon.h"

void Polygon::addPoint(const Vector2D& point)
{
    points.push_back(point);
}

void Polygon::move(const Vector2D& delta)
{
    for (auto&& point : points)
    {
        point.x += delta.x;
        point.y += delta.y;
    }
}

std::ostream& Polygon::serializePoints(std::ostream& os) const
{
    os << '[';
    if (points.size() > 0)
    {
        size_t e = points.size() - 1;
        for (size_t i = 0; i < e; i++)
        {
            points.at(i).serialize(os);
            os << ' ';
        }
        points.at(e).serialize(os);
    }
    return os << ']';
}

std::vector<Vector2D> Polygon::unserializePoints(std::istream& is)
{
    std::vector<Vector2D> points;

    // Check that this is a valid list; a valid list must start with '[' and not
    // empty.
    if (is.get() != '[')
        return points;
    if (is.peek() == ']')
    {
        is.seekg(1, is.cur);
        return points;
    }

    do
    {
        points.push_back(Vector2D::unserialize(is));
    } while (is.get() != ']');

    return points;
}
