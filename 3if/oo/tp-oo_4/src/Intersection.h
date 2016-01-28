#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <istream>
#include <string>
#include <vector>

#include "FigureGroup.h"

class Intersection : public FigureGroup
{
public:
    Intersection() {}
    Intersection(std::vector<Figure*> _figures) : FigureGroup(_figures) {}
    Intersection(const Intersection& otherInter) : FigureGroup(otherInter) {}

    virtual bool contains(const Vector2D& point) const;
    char getType() const { return INTERSECTION; }

    friend std::ostream& operator<<(std::ostream& os, const Intersection* cp);
    friend std::istream& operator>>(std::istream& is, Intersection*& cp);

};

#endif // INTERSECTION_H
