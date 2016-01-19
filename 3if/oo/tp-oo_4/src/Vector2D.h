#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include <istream>

struct Vector2D {
    Vector2D(long _x, long _y) : x(_x), y(_y) {};

    std::string serialize();
    static Vector2D unserialize(std::istream is)
    {
        long x, y;
        char c;
        is >> x >> c >> y;
        return Vector2D(x, y);
    }

    long x;
    long y;
};

#endif // VECTOR2D_H
