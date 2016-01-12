
class Canvas;
class HistoryManager;

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
