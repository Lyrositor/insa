#ifndef HISTORY_MANAGER_H
#define HISTORY_MANAGER_H

#include <string>
#include <vector>

#include "Figure.h"
#include "Vector2D.h"

class Canvas;

struct HistoryEntry
{
    static const char FIGURE = 'F';
    static const char MOVE = 'M';
    static const char GROUP = 'G';

    HistoryEntry(char op) : operation(op) {}

    char operation;
};

typedef std::vector<HistoryEntry*> History;

struct FigureEntry : public HistoryEntry
{
    FigureEntry(std::string n, Figure* f, bool d) :
            HistoryEntry(FIGURE), name(n), figure(f), deleted(d) {}
    ~FigureEntry() { delete figure; }

    std::string name;
    Figure* figure;
    bool deleted;
};

struct MoveEntry : public HistoryEntry
{
    MoveEntry(std::string n, Vector2D d) :
            HistoryEntry(MOVE), name(n), delta(d) {}

    std::string name;
    Vector2D delta;
};

struct GroupEntry : public HistoryEntry
{
    GroupEntry(std::vector<Figure*> g) : HistoryEntry(GROUP), group(g) {}
    ~GroupEntry();

    std::vector<Figure*> group;
};

class HistoryManager
{
public:
    HistoryManager() : current(history.begin()) {}
    ~HistoryManager();

    void addEntry(HistoryEntry* entry);
    bool redo(Canvas* canvas);
    bool undo(Canvas* canvas);

private:
    bool doEntry(HistoryEntry* entry, bool redo);

    History history;
    History::iterator current;
};

#endif // HISTORY_MANAGER_H
