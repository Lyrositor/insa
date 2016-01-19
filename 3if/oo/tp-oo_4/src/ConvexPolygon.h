#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include <vector>
#include "Polygon.h"
#include "Vector2D.h"

class ConvexPolygon : public Polygon
{
public:
    ConvexPolygon(std::vector<Vector2D> _points);

	void appendPoint();

private:
	std::vector<Vector2D> points;
};

#endif // CONVEX_POLYGON_H
