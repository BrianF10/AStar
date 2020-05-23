#ifndef NODE_H
#define NODE_H
#include <point.h>

class Node {
public:
    Node() {
        dist = 0.0;
        cost = 0.0;
    }
    Node(double new_dist, double new_cost) {
        dist = new_dist;
        cost = new_cost;
    }
    bool operator== (const Node& new_node) {
        return current == new_node.current;
    }
    bool operator== (const Point& new_point) {
        return current == new_point;
    }
    bool operator< (const Node& new_node) const {
        bool is;
        is = dist + cost < new_node.dist + new_node.cost;
        return is;
    }
    Point GetParentPoint() const {
        return parent;
    }
    Point GetCurrentPoint() const{
        return current;
    }
    double GetDist() const {
        return dist;
    }
    double GetCost() const {
        return cost;
    }
    void SetCost(int new_cost){
        cost = new_cost;
    }
    void SetDist(int new_dist) {
        dist = new_dist;
    }
    void SetCurrentPoint(const Point& new_point) {
        current = new_point;
    }
    void SetParentPoint(const Point& new_point) {
        parent = new_point;
    }

private:
    Point current, parent;
    double dist, cost;
};

#endif // NODE_H
