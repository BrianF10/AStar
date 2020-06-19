#ifndef POINT_H
#define POINT_H
#include<iostream>

class Point {
public:
    Point() {
        x = 0;
        y = 0;
    }
    Point (int a, int b) {
        x = a;
        y = b;
    }
    bool operator== (const Point& new_point) const{
        return new_point.x == x && new_point.y == y;
    }
    bool operator!= (const Point& new_point) const{
        return !(*this == new_point);
    }
    Point operator+ (const Point& new_point) const{
        Point pp;
        pp.x = new_point.x + x;
        pp.y = new_point.y + y;
        return pp;
    }
    void SetXY(const Point& new_point) {
        x = new_point.x;
        y = new_point.y;
    }
    int GetX() {
        return x;
    }
    int GetY() {
        return y;
    }
    void printPoint() {
        std::cout << "X: " << x << " Y: " << y;
    }
private:
    int x, y;
};

#endif // POINT_H
