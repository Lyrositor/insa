#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include <istream>
#include <ostream>
#include <vector>

#include "Polygon.h"
#include "Vector2D.h"

/** Represents a simple (non-intersecting) convex polygon.
 *
 * Polygons aren't validated on creation; it is the responsiblity of the user
 * to ensure that a valid sequence of points is provided beforehand.
 */
class ConvexPolygon : public Polygon
{
public:
    /** Constructs a convex polygon from its sequence of points.
     *
     * @param _points the sequence of points defining the polygon
     */
    ConvexPolygon(const std::vector<Vector2D>& _points) : Polygon(_points) {};

    /** Checks if the figure contains a point within its bounds.
     *
     * @param point the point to check against
     * @return true if the point is within its bounds, false otherwise
     */
    bool contains(const Vector2D& point) const;

    /** Creates a dynamically-allocated copy of the figure.
     *
     * @return a pointer to the newly-created figure
     */
    Figure* createCopy() const;

    /** Returns the figure's type.
     *
     * Used to quickly determine the type of a figure through its base pointer.
     * @return the figure's type
     */
    char getType() const { return CONVEX_POLYGON; };

    /** Writes a convex polygon to an output stream.
     *
     * @param os the output stream to write to
     * @param cp the convex polygon instance to write
     * @return the provided output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const ConvexPolygon* cp);

    /** Reads a convex polygon from an input stream.
     *
     * @param is the input stream to read from
     * @param cp a pointer to overwrite with the location of a new instance
     * @return the provided input stream
     */
    friend std::istream& operator>>(std::istream& is, ConvexPolygon*& cp);

};

#endif // CONVEX_POLYGON_H
