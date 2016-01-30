#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "FigureGroup.h"

class Intersection : public FigureGroup
{
public:
    Intersection() : FigureGroup() {}
    Intersection(std::vector<Figure*>& _figures) : FigureGroup(_figures) {}
    Intersection(const Intersection& inter) : FigureGroup(inter) {}

    virtual bool contains(const Vector2D& point) const;
    char getType() const { return INTERSECTION; }

    friend std::ostream& operator<<(std::ostream& os, const Intersection* cp);
    friend std::istream& operator>>(std::istream& is, Intersection*& cp);

};

#endif // INTERSECTION_H
