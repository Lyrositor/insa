#ifndef EDITOR_H
#define EDITOR_H

#include <string>
#include <vector>

class Canvas;
class HistoryManager;

enum CMD_RET
{
    ERR,
    OK,
    OK_NO_MSG,
    EXIT
};

class Editor
{
public:
    Editor();
    ~Editor();

    void run();

private:
    static const char DELIM = ' ';

    static const std::string CMD_ADD_SEGMENT;
    static const std::string CMD_ADD_RECTANGLE;
    static const std::string CMD_ADD_CONVEX_POLYGON;
    static const std::string CMD_ADD_UNION;
    static const std::string CMD_ADD_INTERSECTION;
    static const std::string CMD_HIT;
    static const std::string CMD_DELETE;
    static const std::string CMD_MOVE;
    static const std::string CMD_LIST;
    static const std::string CMD_UNDO;
    static const std::string CMD_REDO;
    static const std::string CMD_LOAD;
    static const std::string CMD_SAVE;
    static const std::string CMD_CLEAR;
    static const std::string CMD_EXIT;

    CMD_RET handleInput(std::vector<std::string>& cmd);

    Canvas* canvas;
};

#endif // EDITOR_H
