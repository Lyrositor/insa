#include <list>

class Canvas;

class HistoryManager
{
public:
    void addEntry(HistoryEntry entry);
    void redo(Canvas* canvas);
    void undo(Canvas* canvas);

private:
    std::list<HistoryEntry> history;
    std::iterator current;
};

struct HistoryEntry {
    int type;
    void* data;
};
