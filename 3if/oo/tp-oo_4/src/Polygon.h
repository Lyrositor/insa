#ifndef POLYGON_H
#define POLYGON_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "Figure.h"
#include "Vector2D.h"

/** Represents a simple (non-intersecting) polygon. */
class Polygon : public Figure
{
public:
    /** Constructs a new empty polygon. */
    Polygon() {}

    /** Constructs a new polygon from an initial sequence of points. */
    Polygon(const std::vector<Vector2D>& _points) : points(_points) {}

    /** Checks if the figure contains a point within its bounds.
     *
     * @param point the point to check against
     * @return true if the point is within its bounds, false otherwise
     */
    virtual bool contains(const Vector2D& point) const = 0;

    /** Creates a dynamically-allocated copy of the figure.
     *
     * @return a pointer to the newly-created figure
     */
    virtual Figure* createCopy() const = 0;

    /** Returns the figure's type.
     *
     * Used to quickly determine the type of a figure through its base pointer.
     * @return the figure's type
     */
    virtual char getType() const = 0;

    /** Moves the figure a relative distance.
     *
     * @param delta the vector by which to move the figure
     */
    void move(const Vector2D& delta);

    /** Writes all points out to the stream.
     *
     * @param os the output stream to write to
     * @return the output stream passed as a parameter
     */
    std::ostream& serializePoints(std::ostream& os) const;

    /** Reads a list of points to add from an input stream.
     *
     * @param is the input stream to read from
     * @return the sequence of points read
     */
    static std::vector<Vector2D> unserializePoints(std::istream& is);

protected:
    /** The sequence of points which define the polygon. */
    std::vector<Vector2D> points;

};

#endif // POLYGON_H
