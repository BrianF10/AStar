#include "map.h"
#include <fstream>
#include <string>
#include <iostream>


Map::Map() {
    width = 8;
    height = 8;
    map = new char[width * height];

    char t[64] = {
            '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
            '0', '0', '0', '0', '1', '1', '1', '0', '0', '0', '1', '0', '0', '0', '1', '0',
            '0', '0', '1', '0', '0', '0', '1', '0', '0', '0', '1', '1', '1', '1', '1', '0',
            '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'
    };
    for (int i = 0; i < height * width; ++i) {
        map[i] = t[i];
    }
}

void Map::SetSize() {
    myfile.open(filename.c_str());
    string line;
    int size_rows = 0;
    int size = 0;
    int size_cols = 0;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            size = line.size();
            if (size_cols < size) {
                size_cols = size;				}
                size_rows++;
            }
        }
            //cout << "size_cols" << size_cols << endl;
            //cout << "size_rows" << size_rows << endl;
      myfile.close();
      width = size_cols;
      height = size_rows;
}

Map::Map(const string& new_filename) {
    filename = new_filename;
    SetSize();
    myfile.open(filename.c_str());
    map = new char[width * height];
    string line;
    int i = 0;
    while (getline(myfile, line)) {
        for (int j = 0; j < width; ++j) {
            map[i * width + j] = line[j];
                if (!((j + 1) % width)) {
                    //cout << endl;
                }
        }
    ++i;
    }
}


Map::~Map() {
    myfile.close();
    delete[] map;
}

int Map::operator() (int x, int y) {
        // Y initializes from 0
        //return map[y * width + x];
    if (map[y * width + x] == '1'){
        return 1;
    }
    else{
        return 0;
    }
}
int Map::GetWidth() const {
    return width;
}
int Map::GetHeight() const {
    return height;
}

Map& Map::operator=(const Map& a) {
    int new_width = a.GetWidth();
    int new_height = a.GetHeight();
    char *p = new char[new_width * new_height];
    for (int i = 0; i < new_width * new_height; ++i){
        p[i] = a.map[i];
    }
    delete[] map;
    map = p;
    width = new_width;
    height = new_height;

    return *this;
}
