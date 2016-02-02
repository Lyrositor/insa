#ifndef POLYGON_H
#define POLYGON_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "Figure.h"
#include "Vector2D.h"

class Polygon : public Figure
{
public:
    Polygon(const std::vector<Vector2D>& _points) : points(_points) {};

    virtual char getType() const = 0;

    virtual bool contains(const Vector2D& point) const = 0;
    virtual Figure* createCopy() const = 0;
    void move(const Vector2D& delta);
    std::ostream& serializePoints(std::ostream& os) const;
    static std::vector<Vector2D> unserializePoints(std::istream& is);

protected:
    std::vector<Vector2D> points;

};

#endif // POLYGON_H
