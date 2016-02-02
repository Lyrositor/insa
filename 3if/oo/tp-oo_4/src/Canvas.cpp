#include <iostream>
#include <stdexcept>

#include "Canvas.h"
#include "ConvexPolygon.h"
#include "Figure.h"
#include "HistoryManager.h"
#include "Intersection.h"
#include "Rectangle.h"
#include "Segment.h"
#include "Union.h"

Canvas::Canvas()
{
    historyMgr = new HistoryManager();
}

Canvas::~Canvas()
{
    for (auto&& figure : figures)
        delete figure.second;
    delete historyMgr;
}

bool Canvas::addSegment(
        const std::string& name, const Vector2D& point1, const Vector2D& point2
) {
    if (figures.count(name))
        return false;

    addFigure(name, new Segment(point1, point2));
    return true;
}

bool Canvas::addRectangle(
        const std::string& name, const Vector2D& point1, const Vector2D& point2
) {
    if (figures.count(name))
        return false;

    addFigure(name, new Rectangle(point1, point2));
    return true;
}

bool Canvas::addConvexPolygon(
        const std::string& name, const std::vector<Vector2D>& points
) {
    if (figures.count(name))
        return false;

    addFigure(name, new ConvexPolygon(points));
    return true;
}

bool Canvas::addUnion(
        const std::string& name, const std::vector<std::string>& names
) {
    if (figures.count(name))
        return false;

    Union* figure = new Union();
    try
    {
        for (const std::string& n : names)
            figure->addFigure(figures.at(n)->createCopy());
    }
    catch (std::out_of_range& e)
    {
        delete figure;
        return false;
    }
    addFigure(name, figure);
    return true;
}

bool Canvas::addIntersection(
        const std::string& name, const std::vector<std::string>& names
) {
    if (figures.count(name))
        return false;

    Intersection* figure = new Intersection();
    try
    {
        for (const std::string& n : names)
            figure->addFigure(figures.at(n)->createCopy());
    }
    catch (std::out_of_range& e)
    {
        delete figure;
        return false;
    }
    addFigure(name, figure);
    return true;
}

bool Canvas::contains(const std::string& name, const Vector2D& point) const
{
    if (!figures.count(name))
        return false;
    return figures.at(name)->contains(point);
}

bool Canvas::deleteFigures(const std::vector<std::string>& names)
{
    for (const std::string& name : names)
        if (!figures.count(name))
            return false;
    for (const std::string& name : names)
        deleteFigure(name);
    return true;
}

bool Canvas::move(const std::string& name, const Vector2D& delta)
{
    if (!figures.count(name))
        return false;
    moveFigure(name, delta);
    return true;
}

void Canvas::list() const
{
    for (auto&& figure : figures)
        std::cout << figure.first << ' ' << figure.second << std::endl;
}

bool Canvas::undo()
{
    return historyMgr->undo(this);
}

bool Canvas::redo()
{
    return historyMgr->redo(this);
}

bool Canvas::load(std::istream& input)
{
    std::string name;
    std::unordered_map<std::string, Figure*> newFigures;
    std::vector<HistoryEntry*> entries;
    while (input >> name)
    {
        if (figures.count(name))
        {
            for (auto&& f : newFigures)
                delete f.second;
            return false;
        }
        input >> newFigures[name];
    }
    for (auto&& f : newFigures)
    {
        addFigure(f.first, f.second, false);
        entries.push_back(new FigureEntry(
                f.first, f.second->createCopy(), false
        ));
    }
    historyMgr->addEntry(
            new GroupEntry(entries)
    );
    return true;
}

bool Canvas::save(std::ostream& output) const
{
    for (auto&& figure : figures)
        output << figure.first << ' '<< figure.second << std::endl;
    return true;
}

void Canvas::clear()
{
    std::vector<HistoryEntry*> entries;
    for (auto&& figure : figures)
        entries.push_back(new FigureEntry(
                figure.first, figure.second, true
        ));
    figures.clear();
    historyMgr->addEntry(
            new GroupEntry(entries)
    );
}

void Canvas::addFigure(
        const std::string& name, Figure* figure, bool withHistoryEntry
) {
    figures[name] = figure;
    if (withHistoryEntry)
        historyMgr->addEntry(
                new FigureEntry(name, figure->createCopy(), false)
        );
}

void Canvas::deleteFigure(const std::string& name, bool withHistoryEntry)
{
    Figure* figure = figures.at(name);
    if (withHistoryEntry)
        historyMgr->addEntry(new FigureEntry(name, figure, true));
    else
        delete figure;
    figures.erase(name);
}

void Canvas::moveFigure(const std::string& name, const Vector2D& delta,
                        bool withHistoryEntry) {
    Figure* figure = figures.at(name);
    figure->move(delta);
    if (withHistoryEntry)
        historyMgr->addEntry(new MoveEntry(name, delta));
}
