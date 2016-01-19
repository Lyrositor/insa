#include <iostream>

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
    for (auto figure : figures)
        delete figure.second;
    delete historyMgr;
}

bool Canvas::addSegment(
        const std::string& name, const Vector2D& point1, const Vector2D& point2
) {
    if (figures.count(name))
        return false;

    //Segment* figure = new Segment(point1, point2);
    //addFigure(name, figure, new Segment(*figure));
    return true;
}

bool Canvas::addRectangle(
        const std::string& name, const Vector2D& point1, const Vector2D& point2
) {
    if (figures.count(name))
        return false;

    //Rectangle* figure = new Rectangle(point1, point2);
    //addFigure(name, figure, new Rectangle(*figure));
    return true;
}

bool Canvas::addConvexPolygon(
        const std::string& name, const std::vector<Vector2D>& points
) {
    if (figures.count(name))
        return false;

    //ConvexPolygon* figure = new ConvexPolygon(points);
    //addFigure(name, figure, new ConvexPolygon(*figure));
    return true;
}

bool Canvas::addUnion(
        const std::string& name, const std::vector<std::string>& names
) {
    if (figures.count(name))
        return false;

    /*Union* figure = new Union();
    try
    {
        //for (const std::string& n : names)
        //    figure->addFigure(figures.at(name));
    }
    catch (std::out_of_range& e)
    {
        delete figure;
        return false;
    }
    addFigure(name, figure, new Union(*figure));*/
    return true;
}

bool Canvas::addIntersection(
        const std::string& name, const std::vector<std::string>& names
) {
    if (figures.count(name))
        return false;

    /*Intersection* figure = new Intersection();
    try
    {
        //for (const std::string& n : names)
        //    figure->addFigure(figures.at(name));
    }
    catch (std::out_of_range& e)
    {
        delete figure;
        return false;
    }
    addFigure(name, figure, new Intersection(*figure));*/
    return true;
}

bool Canvas::contains(const std::string& name, const Vector2D& point) const
{
    if (!figures.count(name))
        return false;
    //return figures[name]->contains(point);
    return true;
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
    //figures[name]->move(delta);
    return true;
}

void Canvas::list() const
{
    //for (fig_ptr figure : figures)
    //    std::cout << figure->serialize() << std::endl;
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
    std::string name, parameters;
    char type;
    while (input >> name >> type)
    {
        switch (type)
        {
            case Figure::SEGMENT:
                //addFigure(name, Segment::unserialize(input));
                break;

            case Figure::RECTANGLE:
                //addFigure(name, Rectangle::unserialize(input));
                break;

            case Figure::CONVEX_POLYGON:
                //addFigure(name, ConvexPolygon::unserialize(input));
                break;

            case Figure::UNION:
                //addFigure(name, Union::unserialize(input));
                break;

            case Figure::INTERSECTION:
                //addFigure(name, Intersection::unserialize(input));
                break;

            default:
                return false;
        }
    }
    return true;
}

bool Canvas::save(std::ostream& output) const
{
    /*for (auto figure : figures)
        output << figure.first << " " << figure.second->serialize() <<
                std::endl;*/
    return true;
}

void Canvas::clear()
{
    std::vector<HistoryEntry*> entries;
    for (auto figure : figures)
        entries.push_back(new FigureEntry(figure.first, figure.second, true));
    figures.clear();
    historyMgr->addEntry(
            new GroupEntry(entries)
    );
}

void Canvas::addFigure(
        const std::string& name, Figure* figure, Figure* historyFigure
) {
    figures[name] = figure;
    if (historyFigure != nullptr)
        historyMgr->addEntry(new FigureEntry(name, historyFigure, false));
}

void Canvas::deleteFigure(const std::string& name, bool withHistoryEntry)
{
    Figure* figure = figures.at(name);
    if (withHistoryEntry)
        historyMgr->addEntry(new FigureEntry(name, figure, true));
    figures.erase(name);
}
