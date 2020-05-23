//============================================================================
// Name        : intern_read.cpp
// Author      : Angulo Brian
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <QCoreApplication>
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <string>
#include <point.h>
#include <map.h>
#include <node.h>
#include <dijkstra.h>
#include <astar.h>
//#include <iterator>


using namespace std;

void PrintAStar(Point& start, Point& end, Map& map, string& h_function, int new_eps=1){
    AStar as;
    as.SetHFunc(h_function);
    if (new_eps > 1){
        as.SetEps(new_eps);
    }

    if(as.search(start, end, map)) {
        list<Point> path;
        double c = as.Path(path);
        int width = map.GetWidth();
        int height = map.GetHeight();
        for (int y = -1; y < height + 1; ++y) {
            for (int x = -1; x < width + 1; ++x){
                if(x < 0 || y < 0 || x >=width || y >= height|| map(x, y) == 1){
                    cout << char(0xdb);
                }
                else if( find( path.begin(), path.end(), Point(x, y) )!= path.end()) {
                    cout << "x";
                }
                else{
                    cout << ".";
                }
            }
            cout << "\n";
        }
        cout << "\nPath cost " << c << ": ";
        for(list<Point>::iterator i = path.begin(); i != path.end(); i++ ) {
            int xx = (*i).GetX();
            int yy = (*i).GetY();
            cout<< "(" << xx << ", " << yy << ") ";
        }
        cout << "\n";
    }
}

void PrintDijkstra(Point& start, Point& end, Map& map){
    Dijkstra as;

    if(as.search(start, end, map)) {
        list<Point> path;
        double c = as.Path(path);
        int width = map.GetWidth();
        int height = map.GetHeight();
        for (int y = -1; y < height + 1; ++y) {
            for (int x = -1; x < width + 1; ++x){
                if(x < 0 || y < 0 || x >=width || y >= height|| map(x, y) == 1){
                    cout << char(0xdb);
                }
                else if( find( path.begin(), path.end(), Point(x, y) )!= path.end()) {
                    cout << "x";
                }
                else{
                    cout << ".";
                }
            }
            cout << "\n";
        }
        cout << "\nPath cost " << c << ": ";
        for(list<Point>::iterator i = path.begin(); i != path.end(); i++ ) {
            int xx = (*i).GetX();
            int yy = (*i).GetY();
            cout<< "(" << xx << ", " << yy << ") ";
        }
        cout << "\n";
    }
}

void Mode(Point& new_start, Point& new_end, Map& map, string mode, string h_func, int new_eps=1) {
    if (mode == "A" or mode == "W") {
        if (mode=="A") {
            cout << "mode: AStar" << "\t";
        }else if(mode=="W") {
            cout << "mode: WeightedAStar" << "\t";
            cout << "epsilon: " << new_eps  <<"\t";
        }
        if (h_func == "M") {
            cout << "Heuristic function: Manhatan" << endl;
        }else if(h_func == "C") {
            cout << "Heuristic function: Chevishev" << endl;
        }else {
            cout << "Heuristic function: Euclidean" << endl;
        }
        PrintAStar(new_start, new_end, map, h_func, new_eps);
    }
    else{
        cout << "mode: Dijkstra" << endl;
        PrintDijkstra(new_start, new_end, map);
    }
}

int main(int argc, char *argv[]) {
//int main() {
    QCoreApplication a(argc, argv);
    string mode, h_function;
    int eps=1;
    cout << "Please, insert first letter of mode: " << endl;
    cout <<'\t' << "A for AStar, W for WAStar, or D for Dijkstra mode" << endl;
    cin >> mode;
    if (mode=="A" or mode=="W") {
        cout << "Please, insert first letter of heuristic function name: " << endl;
        //cout <<'\t' << "Manhatan, Chevishev or Euclidean" << endl;
        cout <<'\t' << "M, C or E for Manhatan, Chevishev or Euclidean respectively" << endl;
        cin >> h_function;
        if (mode=="W") {
            cout << "Please, insert epsilon: "<<endl;
            cin >> eps;
        }
        //"Manhatan, Chevishev or Euclidean"
    }
    Map map("test.txt");
    //сначала ширина, а потом высота?? исправить?
    Point start(13,0), end(8, 8);
    Mode(start, end, map, mode, h_function, eps);

    Map map1("filename.txt");
    Point start1(0,0), end1(0, 6);
    Mode(start1, end1, map1, mode, h_function, eps);

    //return 0;
    return a.exec();
}
