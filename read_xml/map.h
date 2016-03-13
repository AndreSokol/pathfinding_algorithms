#ifndef MAP_H
#define MAP_H

#include "gl_settings.h"

class Map
{
public:
    Map();
    ~Map();

    bool GetMapFromXML(const char*);
    friend std::ostream& operator<< (std::ostream &, const Map &);
    void DumpToXML(const char*);
    int GetMapArea();
    int GetHeight();
    int GetWidth();
    int At(int, int);

private:
    int **grid;
    int width;
    int height;
    int cellsize;
    int startx;
    int starty;
    int finishx;
    int finishy;
    std::string map_description;
    Algorithm * algorithm;
    Options * options;
};

#endif // MAP_H
