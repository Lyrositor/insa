#ifndef EDITOR_H
#define EDITOR_H

#include "Canvas.h"
#include "HistoryManager.h"

class Editor
{
public:
    Editor();
    ~Editor();

    void run();

private:
    Canvas* canvas;
    HistoryManager* historyMgr;
};

#endif