#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <vector>

#include "Vector2D.h"

class Canvas;
class Figure;

/** Represents a user operation in the program's history. */
struct HistoryEntry
{
    // Entry types' identifiers
    static const char FIGURE = 'F';
    static const char MOVE = 'M';
    static const char GROUP = 'G';

    /** Destroys the entry; should be sub-classed. */
    virtual ~HistoryEntry() {}

    /** The sub-type of operation. */
    char operation;

protected:
    /** Constructs a new entry of the specified operation type.
     *
     * @param op the operation type of this entry
     */
    HistoryEntry(char op) : operation(op) {}
};

typedef std::vector<HistoryEntry*> History;

/** A figure creation or deletion operation entry. */
struct FigureEntry : public HistoryEntry
{
    /** Creates a new entry for a figure.
     *
     * @param n the figure's name
     * @param f the figure copy to store
     * @param d whether or not the figure was deleted
     */
    FigureEntry(std::string n, Figure* f, bool d) :
            HistoryEntry(FIGURE), name(n), figure(f), deleted(d) {}

    /** Destroys the figure associated with the entry, then the entry. */
    ~FigureEntry() { delete figure; }

    /** The associated figure's name. */
    std::string name;

    /** The figure to re-create, if asked. */
    Figure* figure;

    /** Whether or not the figure was deleted. */
    bool deleted;
};

/** A figure movement operation entry. */
struct MoveEntry : public HistoryEntry
{
    /** Creates a new movement entry.
     *
     * @param n the figure's name
     * @param d the vector by which the figure was moved
     */
    MoveEntry(std::string n, Vector2D d) :
            HistoryEntry(MOVE), name(n), delta(d) {}

    /** The associated figure's name. */
    std::string name;

    /* The vector by which the figure was moved. */
    Vector2D delta;
};

/** A group history entry; all sub-operations are executed as a whole. */
struct GroupEntry : public HistoryEntry
{
    /** Creates a new group of history entries.
     *
     * @param g the collection of history entries to group together
     */
    GroupEntry(std::vector<HistoryEntry*> g) : HistoryEntry(GROUP), group(g) {}

    /** Destroys all sub-entries, followed by this entry. */
    ~GroupEntry();

    /** The collection of sub-entries. */
    std::vector<HistoryEntry*> group;
};

/** Manages the history of user operations in the program. */
class HistoryManager
{
public:
    /** Initializes the manager; by default, it assumes no operations have been
     * executed. */
    HistoryManager() : current(0) { }

    /** Destroys every recorded operation, then destroys the manager. */
    ~HistoryManager();

    /** Records a new user operation.
     *
     * @param entry the user's operation's associated history entry */
    void addEntry(HistoryEntry* entry);

    /** Modifies the canvas to redo an operation, if there is an operation that
     * can be redone.
     *
     * @param canvas the canvas to modify
     * @return true if an operation was successfully redone, false otherwise
     */
    bool redo(Canvas* canvas);

    /** Modifies the canvas to undo an operation, if there is an operation that
     * can be undone.
     *
     * @param canvas the canvas to modify
     * @return true if an operation was successfully undone, false otherwise
     */
    bool undo(Canvas* canvas);

private:
    /** Empties all entries from a certain point in time.
     *
     * To be called when an operation is recorded and some previous future
     * history exists (because the user used undo at least once before).
     * @param start the position to deleting from
     */
    void clearEntries(History::size_type start);

    /** Redoes or undoes a recorded operation.
     *
     * @param canvas the canvas to modify
     * @param entry the operation to undo or redo
     * @param doRedo whether to redo the operation or undo it
     * @return true if the operation was undone or redone, false otherwise
     */
    bool doEntry(Canvas* canvas, HistoryEntry* entry, bool doRedo);

    /** The collection of all previously-executed user operations. */
    History history;

    /** The current position in the history of operations. */
    History::size_type current;
};

#endif // HISTORY_MANAGER_H
