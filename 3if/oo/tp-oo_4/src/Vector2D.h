#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>

struct Vector2D {
    Vector2D(long _x, long _y) : x(_x), y(_y) {};

    std::string serialize();
    void unserialize();

    long x;
    long y;
};

#endif // VECTOR2D_H
