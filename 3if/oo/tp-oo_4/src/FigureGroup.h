#ifndef FIGUREGROUP_H
#define FIGUREGROUP_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "Figure.h"
#include "Vector2D.h"

/** A figure which consists of multiple sub-figures; must be sub-classed. */
class FigureGroup : public Figure
{
public:
    /** Constructs an empty figure group. */
    FigureGroup() {}

    /** Constructs a figure group with a set of initial figures.
     *
     * @param _figures the group's initial figures
     */
    FigureGroup(std::vector<Figure*>& _figures) : figures(_figures) {};

    /** Constructs a figure group from another figure group.
     *
     * @param figureGroup the figure group to copy
     */
    FigureGroup(const FigureGroup& figureGroup);

    /** Assigns another figure group's value to this one.
     *
     * @param figureGroup the figure group to copy
     */
    FigureGroup& operator=(const FigureGroup& figureGroup);

    /** Destroys every sub-figure, then destroys the figure group.
     */
    virtual ~FigureGroup();

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
    virtual void move(const Vector2D& delta);

    /** Adds another figure to the figure group.
     *
     * @param figure a pointer to a figure to add
     */
    void addFigure(Figure* figure);

    /** Writes all sub-figures out to the stream.
     *
     * @param os the output stream to write to
     */
    std::ostream& serializeFigures(std::ostream& os) const;

    /** Reads a list of sub-figures to add from an input stream.
     *
     * @param is the input stream to read from
     */
    static std::vector<Figure*> unserializeFigures(std::istream& is);

protected:
    /** The collection of sub-figures. */
    std::vector<Figure*> figures;
};

#endif // FIGUREGROUP_H
