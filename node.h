#ifndef NODE_H
#define NODE_H
#include <point.h>

class Node {
public:
    Node() {
        h_value = 0.0;
        g_value = 0.0;
    }
    Node(double new_h_value, double new_g_value) {
        h_value = new_h_value;
        g_value = new_g_value;
    }
    bool operator== (const Node& new_node) const{
        return current == new_node.current;
    }
    bool operator!= (const Node& new_node) const {
        return !(*this == new_node);
    }
    bool operator== (const Point& new_point) const{
        return current == new_point;
    }
    bool operator!= (const Point& new_point) const{
        return !(*this == new_point);
    }
    bool operator< (const Node& new_node) const{
        bool is;
        is = h_value + g_value <= new_node.h_value + new_node.g_value;
        return is;
    }
    Point GetParentPoint() const {
        return parent;
    }
    Point GetCurrentPoint() const{
        return current;
    }
    double GetHValue() const {
        return h_value;
    }
    double GetGValue() const {
        return g_value;
    }
    void SetGValue(double new_g_value){
        g_value = new_g_value;
    }
    void SetHValue(double new_h_value) {
        h_value = new_h_value;
    }
    void SetCurrentPoint(const Point& new_point) {
        current = new_point;
    }
    void SetParentPoint(const Point& new_point) {
        parent = new_point;
    }

private:
    Point current, parent;
    double h_value, g_value;
};

namespace std{
template <> struct hash<Node> {
    typedef Node argument_type;
    typedef std::size_t result_type;
    std::size_t operator()(const Node& id) const noexcept {
        Point current = id.GetCurrentPoint();
        return std::hash<int>()(current.GetX() ^ (current.GetY() << 4));
    }
};
}

#endif // NODE_H
