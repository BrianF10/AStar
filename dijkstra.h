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
    double Path();
    void PrintMap(bool okey, Map& new_map);
    void PrintPath(bool okey);
    void PrintDijkstra(Point& new_start, Point& new_end, Map& new_map);
    Map map;
    Point end, start;
    Point const none = Point(-1, -1);
    Point neighbors[8];
    list<Node> open;
    list<Node> closed;
private:
    list<Point> path;
};

#endif // DIJKSTRA_H
