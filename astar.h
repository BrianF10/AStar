#ifndef ASTAR_H
#define ASTAR_H
#include <dijkstra.h>
#include <string>

class AStar : public Dijkstra
{
public:
    AStar() : Dijkstra() {}
    int CalcDist(Point& new_point);
    int ManhattanDist(Point& new_point);
    int ChevyshevDist(Point& new_point);
    double EuclideanDist(Point& new_point);
    double CalculateDist(Point& new_point);
    bool FillOpen(Node& new_node);
    bool search(Point& new_start, Point& new_end, Map& new_map);
    void SetHFunc(string& h_func);
    void SetEps(int new_eps);

    string h_function;
    double eps = 1.0;
};

#endif // ASTAR_H
