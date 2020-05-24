#include "dijkstra.h"
#include <node.h>
#include <map.h>
#include <point.h>
#include <list>
#include <algorithm>
#include <iostream>

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
        if((*it).GetCost() < total_cost) {
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
        stepCost = x < 4 ? 1.0 : 1.0;
        neighbor = new_node.GetCurrentPoint() + neighbors[x];
        if (isValid(neighbor) && (map(neighbor.GetX(), neighbor.GetY()) != 1)) {
            if (neighbor == end){
                nc = stepCost + new_node.GetCost();
                Node closed_node(0, nc);
                closed_node.SetCurrentPoint(end);
                closed_node.SetParentPoint(new_node.GetCurrentPoint());
                closed.push_back(closed_node);
                return true;
            }
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
    bool val_start, val_end, res;
    val_start = isValid(start);
    val_end = isValid(end);
    bool map_start, map_end;
    map_start = map(start.GetX(), start.GetY()) == 0;
    map_end = map(start.GetX(), start.GetY()) == 0;
    res = val_start && val_end && map_start && map_end;
    if (res) {
        Node n_node(0, 0);
        n_node.SetCurrentPoint(new_start);
        n_node.SetParentPoint(none);
        open.push_back(n_node);
        closed.push_back(n_node);
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
    else {
        std::cout << "The specified parameters of points 'start' and 'end' are incorrect." << endl;
        std::cout << "\t" << "Please correct them!" << endl;
        return false;
    }
}

double Dijkstra::Path() {
    double cost = closed.back().GetCost();
    Point parent = closed.back().GetCurrentPoint();
    list<Node>::reverse_iterator i;
    for (i = closed.rbegin(); i != closed.rend(); ++i) {
        if ((*i).GetCurrentPoint() == parent && !((*i).GetCurrentPoint() == none)) {
            path.push_front((*i).GetCurrentPoint());
            parent = (*i).GetParentPoint();
        }
    }
    return cost;
}

void Dijkstra::PrintMap(bool okey, Map& new_map){
    int width = new_map.GetWidth();
    int height = new_map.GetHeight();
    if(okey) {
        for (int y = -1; y < height + 1; ++y) {
            for (int x = -1; x < width + 1; ++x){
                if(x < 0 || y < 0 || x >=width || y >= height|| new_map(x, y) == 1){
                    std::cout << char(0xDB);
                }
                else if( find( path.begin(), path.end(), Point(x, y) ) != path.end()) {
                    std::cout << "x";
                }
                else{
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
}

void Dijkstra::PrintPath(bool okey){
    if(okey) {
        for(list<Point>::iterator i = path.begin(); i != path.end(); i++ ) {
            int xx = (*i).GetX();
            int yy = (*i).GetY();
            std::cout<< "(" << xx << ", " << yy << ") ";
        }
        std::cout << "\n";
    }
}
