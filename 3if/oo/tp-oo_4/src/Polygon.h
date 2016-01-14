#ifndef POLYGON_H
#define POLYGON_H

#include <list>
#include "Vector2D.h"

using namespace std;

class Polygon
{
public:
    Polygon();

protected:
    virtual void addPoint(Vector2D point);
    virtual void serializePoints();
    
private:
    list<Vector2D> points;
};

#endif