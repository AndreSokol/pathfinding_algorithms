#ifndef MAP_H
#define MAP_H

#include "gl_settings.h"

class Map
{
public:
    Map(TiXmlHandle, Logger*);
    ~Map();

    TiXmlElement* DumpToXmlElement();
    int GetMapArea();
    int GetHeight();
    int GetWidth();
    int At(int, int);
    int At(Utils::Coords);

    friend std::ostream& operator<< (std::ostream &, const Map &);
private:
    int **grid;
    int width;
    int height;
    int cellsize;
    int startx;
    int starty;
    int finishx;
    int finishy;
    std::string mapDescription;
    Logger *logger;

    void GetMapFromXML(TiXmlHandle);
};

#endif // MAP_H
