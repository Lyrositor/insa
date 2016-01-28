#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <istream>
#include <ostream>
#include <string>

struct Vector2D {
    Vector2D(long _x, long _y) : x(_x), y(_y) {};

    std::ostream& serialize(std::ostream& os) const;
    static Vector2D unserialize(std::istream& is);

    long x;
    long y;
};

#endif // VECTOR2D_H
