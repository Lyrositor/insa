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

/** Reads user commands and translates them into canvas operations. */
class Editor
{
public:
    /** Initialize a new editor, with a blank starting canvas. */
    Editor();

    /** Destroy the canvas, then the editor. */
    ~Editor();

    /** Listens indefinitely for commands from the user. */
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

    /** Parses a tokenized user command and returns the result.
     *
     * @param cmd a user command, split by its DELIM
     * @return a status code representing success, silent success, error or exit
     */
    CMD_RET handleInput(std::vector<std::string>& cmd);

    /** The associated canvas instance. */
    Canvas* canvas;
};

#endif // EDITOR_H
