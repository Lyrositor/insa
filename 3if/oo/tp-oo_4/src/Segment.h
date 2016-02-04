#ifndef SEGMENT_H
#define SEGMENT_H

#include <istream>
#include <ostream>
#include <string>

#include "Polygon.h"
#include "Vector2D.h"

/** A rectangle defined by its two extremeties. */
class Segment : public Polygon
{
public:
    /** Constructs a new segment from two points.
     * @param point1 the first extremity of the segment
     * @param point2 the second extremeity of the segment
     */
    Segment(const Vector2D& point1, const Vector2D& point2);

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
    char getType() const { return SEGMENT; }

    /** Writes a segment to an output stream.
     *
     * @param os the output stream to write to
     * @param segment the segment instance to write
     * @return the provided output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Segment* segment);

    /** Reads a segment from an input stream.
     *
     * @param is the input stream to read from
     * @param segment a pointer to overwrite with the location of a new instance
     * @return the provided input stream
     */
    friend std::istream& operator>>(std::istream& is, Segment*& segment);

};

#endif // SEGMENT_H
