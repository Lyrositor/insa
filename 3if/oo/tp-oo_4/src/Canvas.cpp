#include <iostream>

#include "Canvas.h"
#include "Figure.h"
#include "HistoryManager.h"

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

bool Canvas::addSegment(std::string name, Vector2D point1, Vector2D point2)
{
    if (figures.count(name))
        return false;

    /*historyMgr->addEntry(
            new FigureEntry(name, new Segment(point1, point2), false)
    );
    figures[name] = new Segment(point1, point2);*/
    return true;
}

bool Canvas::addRectangle(std::string name, Vector2D point1, Vector2D point2)
{
    if (figures.count(name))
        return false;

    /*historyMgr->addEntry(
            new FigureEntry(name, new Rectangle(point1, point2), false)
    );
    figures[name] = new Rectangle(point1, point2);*/
    return true;
}

bool Canvas::addConvexPolygon(std::string name, std::vector<Vector2D> points)
{
    if (figures.count(name))
        return false;

    /*historyMgr->addEntry(
            new FigureEntry(name, new ConvexPolygon(points), false)
    );
    figures[name] = new ConvexPolygon(points);*/
    return true;
}

bool Canvas::addUnion(std::string name, std::vector<std::string> names)
{
    if (figures.count(name))
        return false;

    /*Union* newUnion = new Union();
    try
    {
        for (std::string& n : names)
            newUnion->addFigure(figures.at(name));
    }
    catch (std::out_of_range e)
    {
        delete newUnion;
        return false;
    }
    historyMgr->addEntry(new FigureEntry(name, new Union(*newUnion), false));
    figures[name] = newUnion;*/
    return true;
}

bool Canvas::addIntersection(std::string name, std::vector<std::string> names)
{
    if (figures.count(name))
        return false;

    /*Intersection* newInter = new Intersection();
    try
    {
        for (std::string& n : names)
            newInter->addFigure(figures.at(name));
    }
    catch (std::out_of_range e)
    {
        delete newInter;
        return false;
    }
    historyMgr->addEntry(
            new FigureEntry(name, new Intersection(*newInter), false)
    );
    figures[name] = newInter;*/
    return true;
}

bool Canvas::contains(std::string name, Vector2D point)
{
    //return figures[name]->contains(point);
    return true;
}

bool Canvas::deleteFigures(std::vector<std::string> names)
{
    return true;
}

void Canvas::move(std::string name, Vector2D delta)
{

}

void Canvas::list()
{
    //for (fig_ptr figure : figures)
    //    std::cout << figure->toString() << std::endl;
}

bool Canvas::undo ()
{
    return false;
}

bool Canvas::redo ()
{
    return false;
}

bool Canvas::load(std::istream& input)
{
    return true;
}

bool Canvas::save(std::ostream& output)
{
    return true;
}

void Canvas::clear()
{

}
