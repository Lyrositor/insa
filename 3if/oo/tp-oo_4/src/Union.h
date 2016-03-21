#ifndef UNION_H
#define UNION_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "FigureGroup.h"

/** Represents a union of figures. */
class Union : public FigureGroup
{
public:
    /** Constructs an empty union. */
    Union() : FigureGroup() {}

    /** Constructs a union with a set of initial figures.
     *
     * @param _figures the union's initial figures
     */
    Union(std::vector<Figure*>& _figures) : FigureGroup(_figures) {}

    /** Constructs a union from another union.
     *
     * @param anUnion the union to copy
     */
    Union(const Union& anUnion) : FigureGroup(anUnion) {}

    /** Checks if the figure contains a point within its bounds.
     *
     * A union contains a point if at least one sub-figure contains the point.
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
    char getType() const { return UNION; }

    /** Writes a union to an output stream.
     *
     * @param os the output stream to write to
     * @param un the union instance to write
     * @return the provided output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Union* un);

    /** Reads a union from an input stream.
     *
     * @param is the input stream to read from
     * @param un a pointer to overwrite with the location of a new instance
     * @return the provided input stream
     */
    friend std::istream& operator>>(std::istream& is, Union*& un);

};

#endif // UNION_H
