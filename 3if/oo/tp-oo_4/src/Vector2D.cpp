#include "Vector2D.h"

std::ostream& Vector2D::serialize(std::ostream& os) const
{
    return os << '(' << x << ';' << y << ')';
}

Vector2D Vector2D::unserialize(std::istream& is)
{
    char c;
    long x, y;
    std::string temp;
    is >> c;
    std::getline(is, temp, ';');
    x = std::stoi(temp);
    std::getline(is, temp, ')');
    y = std::stoi(temp);
    return Vector2D(x, y);
}
