#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include "Vector2D.h"

class ConvexPolygon;
class Intersection;
class Rectangle;
class Segment;
class Union;

class Figure
{
public:
    static const char CONVEX_POLYGON = 'C';
    static const char INTERSECTION = 'I';
    static const char RECTANGLE = 'R';
    static const char SEGMENT = 'S';
    static const char UNION = 'U';

    virtual ~Figure() = default;

    template<class T> T* as() { return static_cast<T*>(this); };
    Figure* createCopy();
    virtual char getType() = 0;

    virtual bool contains() = 0;
    virtual void move(Vector2D delta) = 0;
    //virtual std::string serialize();
    //Figure* unserialize();

};

#endif // FIGURE_H
