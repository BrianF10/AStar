#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <string>

using namespace std;

class Map
{
public:
    Map();
    void SetSize();
    Map(const string& new_filename);
    Map& operator = (const Map&);
    ~Map();
    int operator() (int x, int y);
    int GetWidth() const;
    int GetHeight() const;
private:
    string filename;
    ifstream myfile;
    int width;
    int height;
    int* map;
};

#endif // MAP_H
