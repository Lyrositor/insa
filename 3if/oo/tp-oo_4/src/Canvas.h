#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <list>
#include <forward_list>
#include <istream>
#include <ostream>
#include <unordered_map>
#include "Vector2D.h"
//#include "Figure.h"

using namespace std;

class Canvas
{
public:
    Canvas();
    ~Canvas();
    
    void addSegment(string name, Vector2D point1, Vector2D point2);
    void addRectangle(string name, Vector2D point1, Vector2D point2);
    void addConvexPolygon(string name, list<Vector2D*> points);
    void addUnion(string name, forward_list<string*> names);
    void contains(string name, Vector2D point);
    void deleteFigure(string name);
    void move(string name, Vector2D delta);
    void listing();
    void load(istream input);
    void save(ostream output);
    void clear();
    
private:
    //unordered_map<string, Figure*> figures;
};

#endif