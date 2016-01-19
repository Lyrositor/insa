#include "ConvexPolygon.h"

ConvexPolygon::ConvexPolygon(std::vector<Vector2D> _points)
{
    points = _points;
}

void ConvexPolygon::appendPoint(const Vector2D& point)
{
    points.push_back(point);
}

bool ConvexPolygon::contains(Vector2D p)
{
    /* From:
    https://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html */
    
    int i, j;
    bool result = false;
    
    for(i = 0, j = points.size() - 1; i < points.size(); j = i++)
    {
        if((points[i].y > p.y) != (points[j].y > p.y) &&
            (p.x < (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y-points[i].y) + points[i].x))
            {
                result = !result;
            }
    }
    
    return result;
}

std::string ConvexPolygon::serialize()
{
    return std::string(1, getType()) + " " + serializePoints();
}