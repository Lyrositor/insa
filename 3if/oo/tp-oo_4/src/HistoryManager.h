#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <list>
#include "Canvas.h"

struct HistoryEntry {
    int type;
    void* data;
};

class HistoryManager
{
public:
    void addEntry(HistoryEntry entry);
    void redo(Canvas* canvas);
    void undo(Canvas* canvas);

private:
    std::list<HistoryEntry> history;
    //std::iterator current;
};

#endif