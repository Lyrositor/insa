#include "ConvexPolygon.h"
#include "Figure.h"
#include "Intersection.h"
#include "Rectangle.h"
#include "Segment.h"
#include "Union.h"

Figure* Figure::createCopy()
{
    switch (getType())
    {
        /*case Figure::SEGMENT:
            return new Segment(*as<Segment>());
        case Figure::RECTANGLE:
            return new Rectangle(*as<Rectangle>());
        case Figure::CONVEX_POLYGON:
            return new ConvexPolygon(*as<ConvexPolygon>());
        case Figure::UNION:
            return new Union(*as<Union>());
        case Figure::INTERSECTION:
           return new Intersection(*as<Intersection>());*/
        default:
            return nullptr;
    }
}
