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
    void PrintAStar(Point& new_start, Point& new_end, Map& new_map, string& h_function, int n_eps=1);
    string h_function;
    double eps = 1.0;
    void Mode(Point& new_start, Point& new_end, Map& new_map, string mode, string h_func, int n_eps);
};

#endif // ASTAR_H
