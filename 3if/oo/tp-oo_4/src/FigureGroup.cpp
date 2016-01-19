#include "FigureGroup.h"

void FigureGroup::move(Vector2D delta)
{
    
}

std::string FigureGroup::serializeFigures()
{
    std::string line = "";
    for(std::vector<Figure*>::iterator it = figures.begin(); it != figures.end(); ++it)
    {
        line += (*it)->serialize();
    }
    return line;
}

void FigureGroup::addFigure(Figure* figure)
{
    figures.push_back(figure);
}