#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include <vector>
#include "Polygon.h"
#include "Vector2D.h"

class ConvexPolygon : Polygon
{
public:
    ConvexPolygon(std::vector<Vector2D> _points);
    
	void appendPoint();

private:
	std::vector<Vector2D> points;
};

#endif // CONVEXPOLYGON_H
