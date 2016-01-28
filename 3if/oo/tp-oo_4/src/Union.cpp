#include "Union.h"

bool Union::contains(const Vector2D& point) const
{
    for (auto&& figure : figures)
        if (figure->contains(point))
            return true;

    return false;
}

std::ostream &operator<<(std::ostream& os, const Union* un)
{
    return un->serializeFigures(os);
}

std::istream &operator>>(std::istream& is, Union*& un)
{
    un = new Union(FigureGroup::unserializeFigures(is));
    return is;
}
