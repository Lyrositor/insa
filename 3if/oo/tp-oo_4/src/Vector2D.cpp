#include "Vector2D.h"

long Vector2D::cross(Vector2D vector) const {
    return x*vector.y - y*vector.x;
}

Vector2D Vector2D::opposite() const {
    return Vector2D(-x, -y);
}

long Vector2D::scalar(Vector2D vector) const {
    return x*vector.x + y*vector.y;
}

Vector2D Vector2D::sub(Vector2D vector) const {
    return Vector2D(x - vector.x, y - vector.y);
}

std::ostream& Vector2D::serialize(std::ostream& os) const
{
    return os << '(' << x << ';' << y << ')';
}

Vector2D Vector2D::unserialize(std::istream& is)
{
    long x, y;
    std::string temp;
    is.ignore(1);
    std::getline(is, temp, ';');
    x = std::stoi(temp);
    std::getline(is, temp, ')');
    y = std::stoi(temp);
    return Vector2D(x, y);
}
