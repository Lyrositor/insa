#ifndef FIGUREGROUP_H
#define FIGUREGROUP_H

#include <string>
#include <vector>

#include "Figure.h"
#include "Vector2D.h"

class FigureGroup : public Figure
{
public:
    virtual char getType() = 0;
    virtual bool contains(Vector2D point) = 0;
    virtual void move(Vector2D delta);
    virtual std::string serialize() = 0;
    
    std::string serializeFigures();
    void addFigure(Figure* figure);
    
protected:
    std::vector<Figure*> figures;
};

#endif // FIGUREGROUP_H
