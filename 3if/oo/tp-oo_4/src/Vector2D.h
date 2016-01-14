#ifndef VECTOR2D_h
#define VECTOR2D_h

#include "Vector2D.h"

using namespace std;

class Vector2D
{
public:
    Vector2D(int _x, int _y);
    ~Vector2D();

    void serialize();
    void unserialize();
};

#endif