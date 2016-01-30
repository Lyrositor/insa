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
    friend class HistoryManager;

public:
    Canvas();
    ~Canvas();

    bool addSegment(
            const std::string& name, const Vector2D& point1,
            const Vector2D& point2
    );
    bool addRectangle(
            const std::string& name, const Vector2D& point1,
            const Vector2D& point2
    );
    bool addConvexPolygon(
            const std::string& name, const std::vector<Vector2D>& points
    );
    bool addUnion(
            const std::string& name, const std::vector<std::string>& names
    );
    bool addIntersection(
            const std::string& name, const std::vector<std::string>& names
    );

    bool contains(const std::string& name, const Vector2D& point) const;
    bool deleteFigures(const std::vector<std::string>& names);
    bool move(const std::string& name, const Vector2D& delta);
    bool undo();
    bool redo();
    void list() const;
    bool load(std::istream& input);
    bool save(std::ostream& output) const;
    void clear();

private:
    void addFigure(
            const std::string& name, Figure* figure,
            bool withHistoryEntry = true
    );
    void deleteFigure(const std::string& name, bool withHistoryEntry = true);

    std::unordered_map<std::string, Figure*> figures;
    HistoryManager* historyMgr;

};

#endif // CANVAS_H
