#include "FigureGroup.h"

FigureGroup::FigureGroup(const FigureGroup& figureGroup)
{
    for (Figure* figure : figureGroup.figures)
        addFigure(figure->createCopy());
}

FigureGroup& FigureGroup::operator=(const FigureGroup& figureGroup)
{
    for (Figure* figure : figureGroup.figures)
        addFigure(figure->createCopy());
    return *this;
}

FigureGroup::~FigureGroup()
{
    for (Figure* figure : figures)
        delete figure;
}


void FigureGroup::move(const Vector2D& delta)
{
    for (Figure* figure : figures)
        figure->move(delta);
}

void FigureGroup::addFigure(Figure* figure)
{
    figures.push_back(figure);
}

std::ostream& FigureGroup::serializeFigures(std::ostream& os) const
{
    os << '[';
    if (figures.size() > 0)
    {
        size_t e = figures.size() - 1;
        for (size_t i = 0; i < e; i++)
            os << figures.at(i) << ' ';
        os << figures.at(e);
    }
    return os << ']';
}

std::vector<Figure*> FigureGroup::unserializeFigures(std::istream& is)
{
    std::vector<Figure*> figures;

    // Check that this is a valid list; a valid list must start with '[' and not
    // empty.
    if (is.get() != '[')
        return figures;
    if (is.peek() == ']')
    {
        is.seekg(1, is.cur);
        return figures;
    }

    do
    {
        Figure* figure;
        is >> figure;
        figures.push_back(figure);
    } while (is.get() != ']');

    return figures;
}
