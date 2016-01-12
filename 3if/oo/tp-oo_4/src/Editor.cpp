#include "Editor.h"

Editor::Editor()
{
    canvas = new Canvas();
    historyMgr = new HistoryManager();
}

Editor::~Editor()
{
    delete historyMgr;
    delete canvas;
}

void Editor::run()
{

}
