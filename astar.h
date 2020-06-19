#ifndef ASTAR_H
#define ASTAR_H
#include <dijkstra.h>
#include <string>
#define def_eps 1.0;

class AStar : public Dijkstra
{
public:
    AStar() : Dijkstra() {}
    ~AStar() {}
    void SetHFunc(string& h_func);
    void SetEps(int new_eps);
private:
    int ManhattanDist(Point& new_point);
    int ChevyshevDist(Point& new_point);
    double EuclideanDist(Point& new_point);
    double CalculateDist(Point& new_point);
    void SetParameters(Node& new_node, Point& neighbor);
    string h_function;
    double eps = def_eps
};

#endif // ASTAR_H
