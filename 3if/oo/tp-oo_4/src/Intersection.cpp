#include "Intersection.h"

Intersection::Intersection(std::vector<Figure*> _figures)
{
    figures = _figures;
}

bool Intersection::contains(Vector2D point)
{
    for(std::vector<Figure*>::iterator it = figures.begin(); it != figures.end(); ++it)
    {
        if(!((*it)->contains(point)))
        {
            return false;
        }
    }
    return true;
}

std::string Intersection::serialize()
{
    return std::string(1, getType()) + ' ' + serializeFigures();
}