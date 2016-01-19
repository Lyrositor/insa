#include "Polygon.h"

Polygon::Polygon()
{

}

void Polygon::addPoint(Vector2D point)
{
    points.push_back(point);
}

void Polygon::move(Vector2D delta)
{
    
}

std::string Polygon::serializePoints()
{
    std::string line = "";
    for(std::vector<Vector2D>::iterator it = points.begin(); it != points.end(); ++it)
    {
        line += it->serialize();
    }
    return line;
}