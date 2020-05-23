#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <node.h>
#include <map.h>
#include <point.h>
#include <list>
#include <algorithm>

using namespace std;

class Dijkstra
{
public:
    Dijkstra();
    bool isValid(Point& new_point);
    bool existPoint(Point& new_point, double total_cost);
    bool FillOpen(Node& new_node);
    bool search(Point& new_start, Point& new_end, Map& new_map);
    double Path(std::list<Point>& path);
    Map map;
    Point end, start;
    Point neighbors[8];
    list<Node> open;
    list<Node> closed;
};

#endif // DIJKSTRA_H
