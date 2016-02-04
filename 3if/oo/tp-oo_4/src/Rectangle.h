#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <istream>
#include <ostream>
#include <string>

#include "Polygon.h"
#include "Vector2D.h"

/** A rectangle defined by two opposite corner points. */
class Rectangle : public Polygon
{
public:
    /** Constructs a new rectangle from two opposite corner points.
     * @param point1 a corner of the rectangle
     * @param point2 an opposite corner of the rectangle
     */
    Rectangle(const Vector2D& point1, const Vector2D& point2);

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
    char getType() const { return RECTANGLE; }

    /** Writes a rectangle to an output stream.
     *
     * @param os the output stream to write to
     * @param rect the rectangle instance to write
     * @return the provided output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Rectangle* rect);

    /** Reads a rectangle from an input stream.
     *
     * @param is the input stream to read from
     * @param rect a pointer to overwrite with the location of a new instance
     * @return the provided input stream
     */
    friend std::istream& operator>>(std::istream& is, Rectangle*& rect);

};

#endif // RECTANGLE_H
