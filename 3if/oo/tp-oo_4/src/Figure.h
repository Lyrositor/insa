#ifndef FIGURE_H
#define FIGURE_H

#include <istream>
#include <ostream>

#include "Vector2D.h"

/** Represents a geometric 2D figure. */
class Figure
{
public:
    // Symbols identifying specialized types of figures.
    static const char CONVEX_POLYGON = 'C';
    static const char INTERSECTION = 'I';
    static const char RECTANGLE = 'R';
    static const char SEGMENT = 'S';
    static const char UNION = 'U';

    /** Destroys a figure; should be subclassed. */
    virtual ~Figure() {}

    /** Casts this figure's pointer to a specific sub-class pointer.
     *
     * @return a pointer of type T to this figure
     */
    template<class T> const T* as() const { return static_cast<const T*>(this); }

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
    virtual void move(const Vector2D& delta) = 0;

    /** Writes a figure to an output stream.
     *
     * This method automatically determines the sub-type of this class to write
     * it to the stream.
     * @param os the output stream to write to
     * @param figure the figure instance to write
     * @return the provided output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Figure* figure);

    /** Reads a figure from an input stream.
     *
     * This method automatically determines the sub-type of this class as it
     * reads it from the stream.
     * @param is the input stream to read from
     * @param figure a pointer to overwrite with the location of a new instance
     * @return the provided input stream
     */
    friend std::istream& operator>>(std::istream& is, Figure*& figure);

};

#endif // FIGURE_H
