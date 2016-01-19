#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <vector>
#include <string>
#include <istream>

#include "FigureGroup.h"

class Intersection : public FigureGroup
{
public:
    Intersection(std::vector<Figure*> _figures);

    char getType()
    {
        return INTERSECTION;
    }
    bool contains(Vector2D point);
    std::string serialize();
    static Intersection unserialize(std::istream is)
    {
        //return Intersection();
    }
};

#endif // INTERSECTION_H
