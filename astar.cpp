#include "astar.h"
//#include <dijkstra.h>
#include <node.h>
#include <map.h>
#include <point.h>
#include <list>
#include <algorithm>
#include <cmath>
#include <iostream>
#define stepCost 1.0
#define passable_cell 0
#define impassable_cell 1

int AStar::ManhattanDist(Point& new_point) {
    int x, y;
    x = end.GetX() - new_point.GetX();
    y = end.GetY() - new_point.GetY();
    return abs(x) + abs(y);
}

int AStar::ChevyshevDist(Point& new_point) {
    int x, y;
    x = abs(end.GetX() - new_point.GetX());
    y = abs(end.GetY() - new_point.GetY());
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

double AStar::EuclideanDist(Point& new_point) {
    double x, y;
    x = end.GetX() - new_point.GetX();
    y = end.GetY() - new_point.GetY();
    return sqrt(x * x + y * y);
}

double AStar::CalculateDist(Point& new_point) {
    if (h_function == "M"){
        return eps * ManhattanDist(new_point);
    }else if (h_function == "C"){
        return eps * ChevyshevDist(new_point);
    }else{
        return eps * EuclideanDist(new_point);
    }
}

void AStar::SetParameters(Node& new_node, Point& neighbor) {
    double new_g_value;
    double h_value;
    new_g_value = stepCost + new_node.GetGValue();
    h_value = CalculateDist(neighbor);
    if (!existPoint(neighbor, new_g_value + h_value)) {
        Node n_node(h_value, new_g_value);
        n_node.SetCurrentPoint(neighbor);
        n_node.SetParentPoint(new_node.GetCurrentPoint());
        open.insert(n_node);
    }

}

void AStar::SetHFunc(string& h_func) {
    h_function = h_func;
}

void AStar::SetEps(int new_eps) {
    eps = new_eps;
}
