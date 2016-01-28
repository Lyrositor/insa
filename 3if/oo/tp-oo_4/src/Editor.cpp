#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Canvas.h"
#include "Editor.h"
#include "Vector2D.h"

const std::string Editor::CMD_ADD_SEGMENT = "S";
const std::string Editor::CMD_ADD_RECTANGLE = "R";
const std::string Editor::CMD_ADD_CONVEX_POLYGON = "PC";
const std::string Editor::CMD_ADD_UNION = "OR";
const std::string Editor::CMD_ADD_INTERSECTION = "OI";
const std::string Editor::CMD_HIT = "HIT";
const std::string Editor::CMD_DELETE = "DELETE";
const std::string Editor::CMD_MOVE = "MOVE";
const std::string Editor::CMD_LIST = "LIST";
const std::string Editor::CMD_UNDO = "UNDO";
const std::string Editor::CMD_REDO = "REDO";
const std::string Editor::CMD_LOAD = "LOAD";
const std::string Editor::CMD_SAVE = "SAVE";
const std::string Editor::CMD_CLEAR = "CLEAR";
const std::string Editor::CMD_EXIT = "EXIT";

Editor::Editor()
{
    canvas = new Canvas();
}

Editor::~Editor()
{
    delete canvas;
}

void Editor::run()
{
    std::vector<std::string> cmd;
    for (;;)
    {
        if (std::cin.eof())
            break;

        cmd.clear();
        char c;
        std::string item;
        while (std::cin.get(c))
        {
            if (c == DELIM || c == '\n')
            {
                if (!item.empty())
                {
                    cmd.push_back(item);
                    item.clear();
                }
                if (c == '\n')
                    break;
            }
            else
                item += c;
        }
        if (cmd.empty())
            continue;

        switch (handleInput(cmd))
        {
            case ERR:
                std::cout << "ERR" << std::endl;
                break;
            case OK:
                std::cout << "OK" << std::endl;
                break;
            case OK_NO_MSG:
                break;
            case EXIT:
                return;
            default:
                break;
        }
    }
}

CMD_RET Editor::handleInput(std::vector<std::string> & cmd)
{
    // Add a segment
    if (cmd[0] == CMD_ADD_SEGMENT)
    {
        if (cmd.size() != 6)
            return ERR;

        long coords[4];
        for (size_t i = 0; i < 4; i++)
            coords[i] = strtol(cmd[i + 2].c_str(), NULL, 0);
        Vector2D point1 = Vector2D(coords[0], coords[1]);
        Vector2D point2 = Vector2D(coords[2], coords[3]);
        return canvas->addSegment(cmd[1], point1, point2) ? OK : ERR;
    }

    // Add a rectangle
    else if (cmd[0] == CMD_ADD_RECTANGLE)
    {
        if (cmd.size() != 6)
            return ERR;

        long coords[4];
        for (size_t i = 0; i < 4; i++)
            coords[i] = strtol(cmd[i + 2].c_str(), NULL, 0);
        Vector2D point1 = Vector2D(coords[0], coords[1]);
        Vector2D point2 = Vector2D(coords[2], coords[3]);
        return canvas->addRectangle(cmd[1], point1, point2) ? OK : ERR;
    }

    // Add a convex polygon
    else if (cmd[0] == CMD_ADD_CONVEX_POLYGON)
    {
        if (cmd.size() < 8 || cmd.size() % 2 == 1)
            return ERR;

        std::vector<Vector2D> points;
        for (size_t i = 2; i < cmd.size(); i += 2)
            points.emplace_back(
                    strtol(cmd[i].c_str(), NULL, 0),
                    strtol(cmd[i + 1].c_str(), NULL, 0)
            );
        return canvas->addConvexPolygon(cmd[1], points) ? OK : ERR;
    }

    // Create a union from other figures
    else if (cmd[0] == CMD_ADD_UNION)
    {
        if (cmd.size() < 3)
            return ERR;

        std::vector<std::string> names(cmd.begin() + 2, cmd.end());
        return canvas->addUnion(cmd[1], names) ? OK : ERR;
    }

    // Create an intersection from other figures
    else if (cmd[0] == CMD_ADD_INTERSECTION)
    {
        if (cmd.size() < 3)
            return ERR;

        std::vector<std::string> names(cmd.begin() + 2, cmd.end());
        return canvas->addIntersection(cmd[1], names) ? OK : ERR;
    }

    // Check if a figure contains a point
    else if (cmd[0] == CMD_HIT)
    {
        if (cmd.size() != 4)
            return ERR;

        long coords[2];
        for (size_t i = 0; i < 2; i++)
            coords[i] = strtol(cmd[i + 2].c_str(), NULL, 0);
        Vector2D point = Vector2D(coords[0], coords[1]);

        std::cout <<
                (canvas->contains(cmd[1], point) ? "YES" : "NO") << std::endl;
        return OK_NO_MSG;
    }

    // Delete any number of figures
    else if (cmd[0] == CMD_DELETE)
    {
        if (cmd.size() < 2)
            return ERR;

        std::vector<std::string> names(cmd.begin() + 1, cmd.end());
        return canvas->deleteFigures(names) ? OK : ERR;
    }

    // Move a figure a relative distance
    else if (cmd[0] == CMD_MOVE)
    {
        if (cmd.size() != 4)
            return ERR;

        long coords[2];
        for (size_t i = 0; i < 2; i++)
            coords[i] = strtol(cmd[i + 2].c_str(), NULL, 0);
        Vector2D point = Vector2D(coords[0], coords[1]);

        return canvas->move(cmd[1], point) ? OK : ERR;
    }

    // List all figures
    else if (cmd[0] == CMD_LIST)
    {
        if (cmd.size() != 1)
            return ERR;

        canvas->list();
        return OK_NO_MSG;
    }

    // Undo the previous action
    else if (cmd[0] == CMD_UNDO)
    {
        if (cmd.size() != 1)
            return ERR;

        return canvas->undo() ? OK : ERR;
    }


    // Redo the next action
    else if (cmd[0] == CMD_REDO)
    {
        if (cmd.size() != 1)
            return ERR;

        return canvas->redo() ? OK : ERR;
    }

    // Load a canvas from a file
    else if (cmd[0] == CMD_LOAD)
    {
        if (cmd.size() != 2)
            return ERR;

        std::ifstream file(cmd[1]);
        if (!file.is_open())
            return ERR;

        bool result = canvas->load(file);
        file.close();
        return result ? OK : ERR;
    }

    // Save the canvas to a file
    else if (cmd[0] == CMD_SAVE)
    {
        if (cmd.size() != 2)
            return ERR;

        std::ofstream file(cmd[1]);
        if (!file.is_open())
            return ERR;

        bool result = canvas->save(file);
        file.close();
        return result ? OK : ERR;
    }

    // Clears the current canvas (but preserves history)
    else if (cmd[0] == CMD_CLEAR)
    {
        if (cmd.size() != 1)
            return ERR;

        canvas->clear();
        return OK;
    }

    else if (cmd[0] == CMD_EXIT)
    {
        if (cmd.size() != 1)
            return ERR;

        return EXIT;
    }

    return ERR;
}
