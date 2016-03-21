#include "ConvexPolygon.h"
#include "Figure.h"
#include "Intersection.h"
#include "Rectangle.h"
#include "Segment.h"
#include "Union.h"

std::ostream& operator<<(std::ostream& os, const Figure* figure) {
    os << figure->getType() << ' ';

    // Convert a figure to its specialized type, then read it from the stream.
    switch (figure->getType())
    {
        case Figure::SEGMENT:
            os << figure->as<Segment>();
            break;

        case Figure::RECTANGLE:
            os << figure->as<Rectangle>();
            break;

        case Figure::CONVEX_POLYGON:
            os << figure->as<ConvexPolygon>();
            break;

        case Figure::UNION:
            os << figure->as<Union>();
            break;

        case Figure::INTERSECTION:
            os << figure->as<Intersection>();
            break;

        default:
            break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Figure*& figure) {
    char type;
    is >> type;
    is.ignore(1);
    switch (type)
    {
        case Figure::SEGMENT:
            Segment* segment;
            is >> segment;
            figure = segment;
            break;

        case Figure::RECTANGLE:
            Rectangle* rectangle;
            is >> rectangle;
            figure = rectangle;
            break;

        case Figure::CONVEX_POLYGON:
            ConvexPolygon* cp;
            is >> cp;
            figure = cp;
            break;

        case Figure::UNION:
            Union* un;
            is >> un;
            figure = un;
            break;

        case Figure::INTERSECTION:
            Intersection* inter;
            is >> inter;
            figure = inter;
            break;

        default:
            figure = NULL;
    }
    return is;
}
