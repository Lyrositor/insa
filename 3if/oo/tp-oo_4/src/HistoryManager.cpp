#include "Canvas.h"
#include "ConvexPolygon.h"
#include "HistoryManager.h"

GroupEntry::~GroupEntry()
{
    for (HistoryEntry* entry : group)
        delete entry;
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
        clearEntries(current);

    history.push_back(entry);
    current = history.end();
}

bool HistoryManager::redo(Canvas* canvas)
{
    if (current == history.end())
        return false;
    current++;
    return doEntry(canvas, *current, true);
}

bool HistoryManager::undo(Canvas* canvas)
{
    if (current == history.begin())
        return false;
    current--;
    return doEntry(canvas, *current, false);
}

void HistoryManager::clearEntries(History::iterator start)
{
    for (History::iterator it = start; it != history.end(); it++)
        delete *it;
    history.erase(start, history.end());
}

bool HistoryManager::doEntry(Canvas* canvas, HistoryEntry* entry, bool doRedo)
{
    switch (entry->operation)
    {
        case HistoryEntry::FIGURE:
        {
            FigureEntry* fE = static_cast<FigureEntry*>(entry);
            if ((doRedo && fE->deleted) || (!doRedo && !fE->deleted))
            {
                canvas->deleteFigure(fE->name, false);
                return true;
            }
            canvas->addFigure(fE->name, fE->figure->createCopy());
            return true;
        }

        case HistoryEntry::MOVE:
        {
            MoveEntry* mE = static_cast<MoveEntry*>(entry);
            canvas->move(
                    mE->name,
                    doRedo ? mE->delta : Vector2D(-mE->delta.x, -mE->delta.y)
            );
            return true;
        }

        case HistoryEntry::GROUP:
        {
            GroupEntry* gE = static_cast<GroupEntry*>(entry);
            for (HistoryEntry * subEntry : gE->group)
                if (!doEntry(canvas, subEntry, doRedo))
                    return false;
            return true;
        }

        default:
            return false;
    }
}
