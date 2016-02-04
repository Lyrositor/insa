#include "Intersection.h"

bool Intersection::contains(const Vector2D& point) const
{
    if (figures.empty())
        return false;

    for (auto&& figure : figures)
        if (!figure->contains(point))
            return false;

    return true;
}

Figure* Intersection::createCopy() const {
    return new Intersection(*this);
}

std::ostream &operator<<(std::ostream& os, const Intersection* inter)
{
    return inter->serializeFigures(os);
}

std::istream &operator>>(std::istream& is, Intersection*& inter)
{
    std::vector<Figure*> figures = FigureGroup::unserializeFigures(is);
    inter = new Intersection(figures);
    return is;
}
