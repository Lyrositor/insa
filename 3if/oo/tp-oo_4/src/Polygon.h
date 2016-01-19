#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>

#include "Figure.h"
#include "Vector2D.h"

class Polygon : public Figure
{
public:
    Polygon();

protected:
    virtual void addPoint(Vector2D point);
    virtual char getType() = 0;
    virtual bool contains(Vector2D point) = 0;
    virtual std::string serialize() = 0;

    void move(Vector2D delta);
    std::string serializePoints();
    
    std::vector<Vector2D> points;
};

#endif // POLYGON_H
