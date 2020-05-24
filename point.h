#ifndef POINT_H
#define POINT_H

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
    bool operator== (const Point& new_point) {
        bool is;
        is = new_point.x == x && new_point.y == y;
        return is;
    }
    Point operator+ (const Point& new_point) {
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
private:
    int x, y;
};

#endif // POINT_H
