#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <istream>
#include <ostream>
#include <string>

/** Represents a pair of 2D cartesian coordinates. */
struct Vector2D {
    /** Constructs a vector from its cartesian coordinates.
     *
     * @param _x the horizontal coordinate
     * @param _y the vertical coordinate
     */
    Vector2D(long _x, long _y) : x(_x), y(_y) {};

    /** Returns the Z coordinate of the cross product of this vector with
     * another vector.
     *
     * @param vector the other vector
     * @return the Z coordinate of the cross product
     */
    long cross(Vector2D vector) const;

    /** Returns the opposite of this vector, with every coordinate negated.
     *
     * @return the opposite of this vector
     */
    Vector2D opposite() const;

    /** Returns the scalar product of this vector with another vector.
     *
     * @param vector the other vector
     * @return the scalar product
     */
    long scalar(Vector2D vector) const;

    /** Returns the subtraction of another vector to this vector.
     *
     * @param vector the other vector
     * @return the resultant vector
     */
    Vector2D sub(Vector2D vector) const;

    /** Write this vector to an output stream.
     * @param os the output stream to write to
     * @return the provided output stream
     */
    std::ostream& serialize(std::ostream& os) const;

    /** Read a new vector from an input stream.
     * @param is the input stream to read from
     * @return the newly-instanced vector
     */
    static Vector2D unserialize(std::istream& is);

    /** The horizontal coordinate. */
    long x;

    /** The vertical coordinate. */
    long y;

};

#endif // VECTOR2D_H
