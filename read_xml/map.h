#ifndef MAP_H
#define MAP_H

#include "gl_settings.h"

class Algorithm {
public:
    Algorithm();
    ~Algorithm();

    bool GetDataFromXml(TiXmlHandle);
    friend std::ostream& operator<< (std::ostream &, const Algorithm &);
    TiXmlElement* DumpToXmlElement ();
private:

    std::string searchType;
    std::string metricType;
    double hWeight;
    std::string breakingTies;
    double lineCost;
    double diagonalCost;
    bool allowDiagonal;
    bool allowSqueeze;
};


class Options {
public:
    Options();
    ~Options();

    bool GetDataFromXml(TiXmlHandle);
private:
    int logLevel;
    std::string logPath;
    std::string logFileName;
};


class Map
{
public:
    Map();
    ~Map();

    bool GetMapFromXML(const char*);
    friend std::ostream& operator<< (std::ostream &, const Map &);
    void DumpToXML(const char*);
    double CalculateDensity();

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


template <typename Type>
std::string toString(const Type &);

template <typename Type>
void ReportTagMissing(const std::string &, const Type &);

#endif // MAP_H
