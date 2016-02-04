#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "FigureGroup.h"

/** Represents an intersection of figures. */
class Intersection : public FigureGroup
{
public:
    /** Constructs an empty intersection. */
    Intersection() : FigureGroup() {}

    /** Constructs an intersection with a set of initial figures.
     *
     * @param _figures the intersection's initial figures
     */
    Intersection(std::vector<Figure*>& _figures) : FigureGroup(_figures) {}

    /** Constructs an intersection from another intersection.
     *
     * @param inter the intersection to copy
     */
    Intersection(const Intersection& inter) : FigureGroup(inter) {}

    /** Checks if the figure contains a point within its bounds.
     *
     * An intersection contains a point if all sub-figures contain the point.
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
    char getType() const { return INTERSECTION; }

    /** Writes an intersection to an output stream.
     *
     * @param os the output stream to write to
     * @param cp the intersection instance to write
     * @return the provided output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Intersection* cp);

    /** Reads a figure from an input stream.
     *
     * @param is the input stream to read from
     * @param cp a pointer to overwrite with the location of the new instance
     * @return the provided input stream
     */
    friend std::istream& operator>>(std::istream& is, Intersection*& cp);

};

#endif // INTERSECTION_H
