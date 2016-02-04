#ifndef CANVAS_H
#define CANVAS_H

#include <istream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "Vector2D.h"

class Figure;
class HistoryManager;

/** Manages the interactions between the model and the user.
 *
 * The canvas is the main component of the program, and ties together all other
 * operations.
 */
class Canvas
{
    friend class HistoryManager;

public:
    /** Constructs a new, empty canvas.
     */
    Canvas();

    /** Empties the canvas and destroys it.
     */
    ~Canvas();

    /** Adds a new segment to the canvas.
     *
     * @param name the name of the segment
     * @param point1 the first end-point of the segment
     * @param point2 the second end-point of the segment
     * @return true if the segment was created and added, false otherwise
     */
    bool addSegment(
            const std::string& name, const Vector2D& point1,
            const Vector2D& point2
    );

    /** Adds a new rectangle to the canvas.
     *
     * @param name the name of the rectangle
     * @param point1 one corner of the rectangle
     * @param point2 another corner of the rectangle, opposite of the first
     * @return true if the rectangle was created and added, false otherwise
     */
    bool addRectangle(
            const std::string& name, const Vector2D& point1,
            const Vector2D& point2
    );

    /** Adds a new convex polygon to the canvas.
     *
     * The series of provided points must form a simple polygon, otherwise
     * correct behaviour is nor guaranteed; only if it is a simple polygon will
     * the convexity validation succeed.
     * @param name the name of the convex polygon
     * @param points the sequence of vertices for the polygon
     * @return true if the convex polygon was created and added, false otherwise
     */
    bool addConvexPolygon(
            const std::string& name, const std::vector<Vector2D>& points
    );

    /** Adds a new figure union to the canvas.
     *
     * The union will copy all the provided figures, ensuring that a
     * modification to the original figures will not affect the union.
     * @param name the name of the union
     * @param names the names of the constituent figures
     * @return true if the union was created and added, false otherwise
     */
    bool addUnion(
            const std::string& name, const std::vector<std::string>& names
    );

    /** Adds a new figure intersection to the canvas.
     *
     * The intersection will copy all the provided figures, ensuring that a
     * modification to the original figures will not affect the intersection.
     * @param name the name of the intersection
     * @param names the names of the constituent figures
     * @return true if the intersection was created and added, false otherwise
     */
    bool addIntersection(
            const std::string& name, const std::vector<std::string>& names
    );

    /** Checks if a figure contains a certain point within its bounds.
     *
     * @param name the name of the figure to check
     * @param point the point to check
     * @return true if the point is in the figure, false otherwise
     */
    bool contains(const std::string& name, const Vector2D& point) const;

    /** Deletes a list of figures.
     *
     * If even one of the provided names does not correspond to a valid figure,
     * no deletion is performed for any figure.
     * @param names a list of names of figures to delete
     * @return true if all figures were deleted, false otherwise
     */
    bool deleteFigures(const std::vector<std::string>& names);

    /** Moves a figure a relative distance.
     *
     * @param name the name of the figure to move
     * @param delta the vector by which to move the figure
     * @return true if the figure was successfully moved, false otherwise
     */
    bool move(const std::string& name, const Vector2D& delta);

    /** Undoes the effects of the previous model-changing operation.
     *
     * @return true if the operation could be undone, false otherwise
     */
    bool undo();

    /** Redoes the effects of the next model-changing operation.
     *
     * Only possible after a call to undo(); if the model was changed since the
     * last call to undo(), all of the undone history is lost, and redo() fails.
     * @return true if the operation could be redone, false otherwise
     */
    bool redo();

    /** Displays a list of all figures currently in the model. */
    void list() const;

    /** Loads a canvas from the specified file stream.
     *
     * The figures are created in addition to any existing figures in the
     * canvas; if any figure shares the same name as one that already exists in
     * this canvas, the load fails and no figures are added.
     * @param input the input stream to read from
     * @return true if a canvas was successfully loaded, false otherwise
     */
    bool load(std::istream& input);

    /** Saves the current state of the model to the specified file stream.
     *
     * @param output the output stream to write to
     * @return true if the save was successful
     */
    bool save(std::ostream& output) const;

    /** Deletes all figures currently on the canvas.
     *
     * This operation is saved in the history, so it can be undone and redone.
     */
    void clear();

private:
    /** Adds an initialized figure to the collection of figures.
     *
     * @param name the name of the figure to add
     * @param figure a pointer to the initialized figure
     * @param withHistoryEntry records this addition in history if true
     */
    void addFigure(
            const std::string& name, Figure* figure,
            bool withHistoryEntry = true
    );

    /** Deletes a figure from the model.
     * @param name the name of the figure to delete
     * @param withHistoryEntry records this deletion in history if true
     */
    void deleteFigure(const std::string& name, bool withHistoryEntry = true);

    /** Moves a figure a relative distance.
     *
     * @param name the name of the figure
     * @param delta the vector by which to move the figure
     * @param withHiistoryEntry records this movement in history if true
     */
    void moveFigure(
            const std::string& name, const Vector2D& delta,
            bool withHistoryEntry = true
    );

    /** The collection of figures currently in the model. */
    std::map<std::string, Figure*> figures;

    /** The history manager, responsible for managing undo's and redo's. */
    HistoryManager* historyMgr;

};

#endif // CANVAS_H
