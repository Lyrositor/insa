#ifndef UNION_H
#define UNION_H

#include <istream>
#include <string>
#include <vector>

#include "FigureGroup.h"

class Union : public FigureGroup
{
public:
    Union() : FigureGroup() {}
    Union(std::vector<Figure*> _figures) : FigureGroup(_figures) {}
    Union(const Union& otherUnion) : FigureGroup(otherUnion) {}

    virtual bool contains(const Vector2D& point) const;
    char getType() const { return UNION; }

    friend std::ostream& operator<<(std::ostream& os, const Union* cp);
    friend std::istream& operator>>(std::istream& is, Union*& cp);

};

#endif // UNION_H
