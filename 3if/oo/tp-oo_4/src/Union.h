#ifndef UNION_H
#define UNION_H

#include <vector>
#include <string>
#include <istream>

#include "FigureGroup.h"

class Union : public FigureGroup
{
public:
    Union(std::vector<Figure*> _figures);

    char getType()
    {
        return UNION;
    }
    bool contains(Vector2D point);
    std::string serialize();
    static Union unserialize(std::istream is)
    {
        //return Union();
    }
};

#endif // UNION_H
