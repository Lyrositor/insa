#include "HistoryManager.h"

GroupEntry::~GroupEntry()
{
    for (Figure* figure : group)
        delete figure;
}

HistoryManager::~HistoryManager()
{
    for (HistoryEntry* entry : history)
        delete entry;
}

void HistoryManager::addEntry(HistoryEntry* entry)
{
    // Discard any previous future actions.
    if (current != history.end())
        history.erase(current, history.end());

    history.push_back(entry);
    current = history.end();
}

bool HistoryManager::redo(Canvas* canvas)
{
    if (current == history.end())
        return false;
    current++;
    return doEntry(*current, true);
}

bool HistoryManager::undo(Canvas* canvas)
{
    if (current == history.begin())
        return false;
    current--;
    return doEntry(*current, false);
}

bool HistoryManager::doEntry(HistoryEntry* entry, bool redo)
{
    switch (entry->operation)
    {
        case HistoryEntry::FIGURE:
            return true;
        case HistoryEntry::MOVE:
            return true;
        case HistoryEntry::GROUP:
            return true;
        default:
            return false;
    }
}
