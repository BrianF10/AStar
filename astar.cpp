#include "astar.h"
//#include <dijkstra.h>
#include <node.h>
#include <map.h>
#include <point.h>
#include <list>
#include <algorithm>
#include <cmath>


int AStar::CalcDist(Point& new_point) {
    int x, y;
    x = abs(end.GetX() - new_point.GetX());
    y = abs(end.GetY() - new_point.GetY());
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

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

bool AStar::FillOpen(Node& new_node) {
    double stepCost, nc;
    double dist;
    Point neighbor;
    for (int x = 0; x < 8; ++x) {
        stepCost = x < 4 ? 1.0 : 1.0;
        neighbor = new_node.GetCurrentPoint() + neighbors[x];
        if (neighbor == end ){
            return true;
        }
        if (isValid(neighbor) && (map(neighbor.GetX(), neighbor.GetY()) != 1)) {
            nc = stepCost + new_node.GetCost();
            dist = CalculateDist(neighbor);
            if (!existPoint(neighbor, nc + dist)) {
                Node n_node(dist, nc);
                n_node.SetCurrentPoint(neighbor);
                n_node.SetParentPoint(new_node.GetCurrentPoint());
                open.push_back(n_node);
            }
        }

    }
    return false;
}

bool AStar::search(Point& new_start, Point& new_end, Map& new_map) {
    end = new_end;
    start = new_start;
    map = new_map;
    Node n_node(CalculateDist(new_start), 0);
    n_node.SetCurrentPoint(new_start);
    open.push_back(n_node);
    while(!open.empty()) {
        open.sort();
        Node current = open.front();
        open.pop_front();
        closed.push_back(current);
        if(FillOpen(current)) {
            return true;
        }
    }
    return false;
}

void AStar::SetHFunc(string& h_func) {
    h_function = h_func;
}

void AStar::SetEps(int new_eps) {
    eps = new_eps;
}