#ifndef SEGMENT_H
#define SEGMENT_H

#include <istream>
#include <ostream>
#include <string>

#include "Polygon.h"
#include "Vector2D.h"

class Segment : public Polygon
{
public:
    Segment(const Vector2D& point1, const Vector2D& point2) :
            Polygon({point1, point2}) {};

    bool contains(const Vector2D& point) const;
    Figure* createCopy() const;
    char getType() const { return SEGMENT; }

    friend std::ostream& operator<<(std::ostream& os, const Segment* segment);
    friend std::istream& operator>>(std::istream& is, Segment*& segment);

};

#endif // SEGMENT_H
