#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <node.h>
#include <map.h>
#include <point.h>
#include <list>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

class Dijkstra
{
public:
    Dijkstra();
    virtual ~Dijkstra() {}
    virtual void SetParameters(Node& new_node, Point& neighbor);
    void PrintMap(bool okey, Map& new_map);
    void PrintPath(bool okey);
    void PrintDijkstra(Point& new_start, Point& new_end, Map& new_map);
    bool search(Point& new_start, Point& new_end, Map& new_map);
protected:
    bool isValid(Point& new_point);
    bool existPoint(Point& new_point, double total_cost);
    void expand_cell(Node& new_node);
    void GetPath();
    Map map;
    Point end, start;
    Point const none = Point(-1, -1);
    Point offset[8];
    set<Node> open;
    unordered_set<Node> close;
    list<Point> path;
};

#endif // DIJKSTRA_H
