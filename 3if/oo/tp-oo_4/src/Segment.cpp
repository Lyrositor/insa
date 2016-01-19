#include <math.h>

#include "Segment.h"

Segment::Segment(Vector2D point1, Vector2D point2)
{
    points.push_back(point1);
    points.push_back(point2);
}

bool Segment::contains(Vector2D point)
{
    float AB = sqrt((points[1].x - points[0].x) * (points[1].x - points[0].x) + (points[1].y - points[0].y) * (points[1].y - points[0].y));
    float AP = sqrt((point.x - points[0].x) * (point.x - points[0].x) + (point.y - points[0].y) * (point.y - points[0].y));
    float PB = sqrt((points[1].x - point.x) * (points[1].x - point.x) + (points[1].y - point.y) * (points[1].y - point.y));
    if(AB == AP + PB)
    {
        return true;
    }
    return false;
}

std::string Segment::serialize()
{
    return std::string(1, getType()) + ' ' + serializePoints();
}