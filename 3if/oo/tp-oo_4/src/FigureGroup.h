#ifndef FIGUREGROUP_H
#define FIGUREGROUP_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

#include "Figure.h"
#include "Vector2D.h"

class FigureGroup : public Figure
{
public:
    FigureGroup() {}
    FigureGroup(std::vector<Figure*>& _figures) : figures(_figures) {};
    FigureGroup(const FigureGroup& figureGroup);
    FigureGroup& operator=(const FigureGroup& figureGroup);
    virtual ~FigureGroup();

    virtual bool contains(const Vector2D& point) const = 0;
    virtual Figure* createCopy() const = 0;
    virtual char getType() const = 0;
    virtual void move(const Vector2D& delta);

    void addFigure(Figure* figure);
    std::ostream& serializeFigures(std::ostream& os) const;
    static std::vector<Figure*> unserializeFigures(std::istream& is);

protected:
    std::vector<Figure*> figures;
};

#endif // FIGUREGROUP_H
