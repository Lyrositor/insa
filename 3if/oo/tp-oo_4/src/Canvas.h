#ifndef CANVAS_H
#define CANVAS_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Vector2D.h"

class Figure;
class HistoryManager;

class Canvas
{
public:
    Canvas();
    ~Canvas();

    bool addSegment(std::string name, Vector2D point1, Vector2D point2);
    bool addRectangle(std::string name, Vector2D point1, Vector2D point2);
    bool addConvexPolygon(std::string name, std::vector<Vector2D> points);
    bool addUnion(std::string name, std::vector<std::string> names);
    bool addIntersection(std::string name, std::vector<std::string> names);
    bool contains(std::string name, Vector2D point);
    bool deleteFigures(std::vector<std::string> name);
    void move(std::string name, Vector2D delta);
    bool undo();
    bool redo();
    void list();
    bool load(std::istream& input);
    bool save(std::ostream& output);
    void clear();

private:
    std::unordered_map<std::string, Figure*> figures;
    HistoryManager* historyMgr;

};

#endif
