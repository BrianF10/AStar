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

using namespace std;

void Mode(Point& new_start, Point& new_end, Map& new_map, string mode, string h_func, int new_eps) {
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
        AStar as;
        as.SetHFunc(h_func);
        if(mode == "W") {
            if (new_eps > 1){
                as.SetEps(new_eps);
            }
        }
        bool is_found;
        is_found = as.search(new_start, new_end, new_map);
        if(is_found) {
            as.PrintMap(is_found, new_map);
            as.PrintPath(is_found);
        }else{
            cout << "Path not found!" <<endl;
        }
    }else{
        cout << "mode: Dijkstra" << endl;
        Dijkstra ds;
        bool is_found;
        is_found = ds.search(new_start, new_end, new_map);
        if(is_found) {
            ds.PrintMap(is_found, new_map);
            ds.PrintPath(is_found);
        }else{
            cout << "Path not found!" <<endl;
        }
    }
}

int main() {
    string mode, h_function;
    int eps=1;
    string namefile;
    int start_x, start_y;
    int end_x, end_y;
    cout << "Please, insert first letter of mode: " << endl;
    cout <<'\t' << "A for AStar, W for WAStar, or D for Dijkstra mode" << endl;
    cin >> mode;
    if (mode=="A" or mode=="W") {
        cout << "Please, insert first letter of heuristic function name: " << endl;
        cout <<'\t' << "M, C or E for Manhatan, Chevishev or Euclidean respectively" << endl;
        cin >> h_function;
        if (mode=="W") {
            cout << "Please, insert epsilon: "<<endl;
            cin >> eps;
        }
        //"Manhatan, Chevishev or Euclidean"
    }
    cout << "Please, insert name's file" << endl;
    cin >> namefile;
    cout << "Please, insert coordinates of start (int x, int y): " << endl;
    cin >> start_x >> start_y;
    cout << "Please, insert coordinates of end (int x, int y): " << endl;
    cin >> end_x >> end_y;
    Map map(namefile);
    Point start(start_x, start_y), end(end_x, end_y);
    Mode(start, end, map, mode, h_function, eps);
    cout << endl;

    return 0;
}
