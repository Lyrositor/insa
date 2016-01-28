#include "Intersection.h"

bool Intersection::contains(const Vector2D& point) const
{
    for (auto&& figure : figures)
        if (!figure->contains(point))
            return false;

    return true;
}

std::ostream &operator<<(std::ostream& os, const Intersection* inter)
{
    return inter->serializeFigures(os);
}

std::istream &operator>>(std::istream& is, Intersection*& inter)
{
    inter = new Intersection(FigureGroup::unserializeFigures(is));
    return is;
}
