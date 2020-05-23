#include "dijkstra.h"
#include <node.h>
#include <map.h>
#include <point.h>
#include <list>
#include <algorithm>



Dijkstra::Dijkstra() {
    neighbors[0] = Point( -1, -1 ); neighbors[1] = Point(  1, -1 );
    neighbors[2] = Point( -1,  1 ); neighbors[3] = Point(  1,  1 );
    neighbors[4] = Point(  0, -1 ); neighbors[5] = Point( -1,  0 );
    neighbors[6] = Point(  0,  1 ); neighbors[7] = Point(  1,  0 );
}

bool Dijkstra::isValid(Point& new_point) {
    bool inside_map, inside_map1;
    inside_map = new_point.GetX() > -1 && new_point.GetY() > -1;
    inside_map1 = new_point.GetX() < map.GetWidth() && new_point.GetY() < map.GetHeight();
    return inside_map && inside_map1;
}

bool Dijkstra::existPoint(Point& new_point, double total_cost) {
    list<Node>::iterator it;
    it = find(closed.begin(), closed.end(), new_point);
    if(it != closed.end()) {
        return true;
    }
    it = find(open.begin(), open.end(), new_point);
    if(it != open.end()) {
        if((*it).GetCost() + (*it).GetDist() < total_cost) {
            return true;
        }
        else{
            open.erase(it);
            return false;
        }
    }
    return false;
}

bool Dijkstra::FillOpen(Node& new_node) {
    double stepCost, nc;
    Point neighbor;
    for (int x = 0; x < 8; ++x) {
        stepCost = x < 4 ? 1.0 : 1;
        neighbor = new_node.GetCurrentPoint() + neighbors[x];
        if (neighbor == end){
            return true;
        }
        if (isValid(neighbor) && (map(neighbor.GetX(), neighbor.GetY()) != 1)) {
            nc = stepCost + new_node.GetCost();
            if (!existPoint(neighbor, nc)) {
                Node n_node(0, nc);
                n_node.SetCurrentPoint(neighbor);
                n_node.SetParentPoint(new_node.GetCurrentPoint());
                open.push_back(n_node);
            }
        }
    }
    return false;
}

bool Dijkstra::search(Point& new_start, Point& new_end, Map& new_map) {
    end = new_end;
    start = new_start;
    map = new_map;
    Node n_node(0, 0);
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

double Dijkstra::Path(list<Point>& path) {
    path.push_front(end);
    double cost = 1 + closed.back().GetCost();
    path.push_front(closed.back().GetCurrentPoint());
    Point parent = closed.back().GetParentPoint();
    list<Node>::reverse_iterator i;
    for (i = closed
         .rbegin(); i != closed.rend(); ++i) {
        if ((*i).GetCurrentPoint() == parent && !((*i).GetCurrentPoint() == start)) {
            path.push_front((*i).GetCurrentPoint());
            parent = (*i).GetParentPoint();
        }
    }
    path.push_front(start);
    return cost;
}
