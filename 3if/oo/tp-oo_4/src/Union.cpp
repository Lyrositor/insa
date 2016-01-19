#include "Union.h"

Union::Union(std::vector<Figure*> _figures)
{
    figures = _figures;
}

bool Union::contains(Vector2D point)
{
    for(std::vector<Figure*>::iterator it = figures.begin(); it != figures.end(); ++it)
    {
        if((*it)->contains(point))
        {
            return true;
        }
    }
    return false;
}

std::string Union::serialize()
{
    return std::string(1, getType()) + ' ' + serializeFigures();
}
