#include "dijkstra.h"
#include <node.h>
#include <map.h>
#include <point.h>
#include <list>
#include <algorithm>
#include <iostream>
#define stepCost 1.0
#define passable_cell 0
#define impassable_cell 1


Dijkstra::Dijkstra() {
    int n = 0;
    for (int i = -1; i < 2; ++i){
        for (int j = -1; j < 2; ++j){
            if (i == 0 and j ==0){

            }else {
                offset[n] = Point(i, j);
                ++n;
            }
        }
    }
}

bool Dijkstra::isValid(Point& new_point) {
    bool inside_map, inside_map1;
    inside_map = new_point.GetX() > -1 && new_point.GetY() > -1;
    inside_map1 = new_point.GetX() < map.GetWidth() && new_point.GetY() < map.GetHeight();
    return inside_map && inside_map1;
}

bool Dijkstra::existPoint(Point& new_point, double total_cost) {
    set<Node>::iterator it;
    unordered_set<Node>::iterator it1;
    it1 = find(close.begin(), close.end(), new_point);
    if(it1 != close.end()) {
        return true;
    }
    it = find(open.begin(), open.end(), new_point);
    if(it != open.end()) {
        if((*it).GetGValue() < total_cost) {
            return true;
        }
        else{
            open.erase(it);
            return false;
        }
    }
    return false;
}

void Dijkstra::SetParameters(Node& new_node, Point& neighbor) {
    double new_g_value;
    new_g_value = stepCost + new_node.GetGValue();
    if (!existPoint(neighbor, new_g_value)) {
        Node n_node(0, new_g_value);
        n_node.SetCurrentPoint(neighbor);
        n_node.SetParentPoint(new_node.GetCurrentPoint());
        open.insert(n_node);
    }
}

void Dijkstra::expand_cell(Node& new_node) {
    bool is_passable_cell;
    Point neighbor;
    for (int x = 0; x < 8; ++x) {
        neighbor = new_node.GetCurrentPoint() + offset[x];
        is_passable_cell = map(neighbor.GetX(), neighbor.GetY()) != impassable_cell;
        if (isValid(neighbor) && is_passable_cell) {
            SetParameters(new_node, neighbor);
        }
    }
}

bool Dijkstra::search(Point& new_start, Point& new_end, Map& new_map) {
    end = new_end;
    start = new_start;
    map = new_map;
    bool val_start, val_end, is_correct;
    bool map_start, map_end;
    val_start = isValid(start);
    val_end = isValid(end);
    map_start = map(start.GetX(), start.GetY()) == passable_cell;
    map_end = map(start.GetX(), start.GetY()) == passable_cell;
    is_correct = val_start && val_end && map_start && map_end;
    if (is_correct) {
        Node n_node;
        n_node.SetCurrentPoint(new_start);
        n_node.SetParentPoint(none);
        open.insert(n_node);
        while(!open.empty()) {
            Node current = *open.begin();
            open.erase(open.begin());
            if (current == end) {
                double new_g_value;
                new_g_value = stepCost + current.GetGValue();
                current.SetGValue(new_g_value);
                close.insert(current);
                GetPath();
                return true;
            }
            close.insert(current);
            expand_cell(current);
        }
        return false;
    }
    else {
        std::cout << "The specified parameters of points 'start' and 'end' are incorrect." << endl;
        std::cout << "\t" << "Please correct them!" << endl;
        return false;
    }
}

void Dijkstra::GetPath() {
    Point parent = end;
    unordered_set<Node>::iterator i;
    while(true){
        i = find(close.begin(), close.end(), parent);
        if ((*i).GetCurrentPoint() == parent) {
            path.push_front((*i).GetCurrentPoint());
            parent = (*i).GetParentPoint();
        }
        if ((*i).GetCurrentPoint() == start) {
            break;
        }
    }
}

void Dijkstra::PrintMap(bool okey, Map& new_map){
    int width = new_map.GetWidth();
    int height = new_map.GetHeight();
    list<Point> path_open;
    for(unordered_set<Node>::iterator i1 = close.begin(); i1 != close.end(); i1++){
        path_open.push_front((*i1).GetCurrentPoint());
    }
    if(okey) {
        for (int y = -1; y < height + 1; ++y) {
            for (int x = -1; x < width + 1; ++x){
                if(x < 0 || y < 0 || x >=width || y >= height|| new_map(x, y) == impassable_cell){
                    std::cout << char(0xDB);
                }
                else if( find( path.begin(), path.end(), Point(x, y) ) != path.end()) {
                    std::cout << "x";
                }
                else if( find( path_open.begin(), path_open.end(), Point(x, y) ) != path_open.end()) {
                    std::cout << "@";
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
    double cost;
    unordered_set<Node>::iterator i;
    i = find(close.begin(), close.end(), end);
    cost = (*i).GetGValue();
    std::cout << "Total g_value: " << cost << endl;
    std::cout << "Size of open " << open.size() << endl;
    std::cout << "Size of close " << close.size() << endl;
    if(okey) {
        for(list<Point>::iterator i = path.begin(); i != path.end(); i++ ) {
            int xx = (*i).GetX();
            int yy = (*i).GetY();
            std::cout<< "(" << xx << ", " << yy << ") ";
        }
        std::cout << "\n";
    }
}
