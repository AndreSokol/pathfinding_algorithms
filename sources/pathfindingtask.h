#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "gl_settings.h"
#include "algorithms/basepathfinder.h"
#include "logger.h"
#include "map.h"
#include "utils.h"

class PathfindingTask {
public:
    PathfindingTask(TiXmlHandle, Logger*);
    ~PathfindingTask();

    void FindPath(Map *);

    friend std::ostream& operator<< (std::ostream &, const PathfindingTask &);

    TiXmlElement* DumpToXmlElement();
private:
    int startx;
    int starty;
    int finishx;
    int finishy;

    std::string searchType;
    std::string metricType;
    double hWeight;
    std::string breakingTies;
    double lineCost;
    double diagonalCost;
    bool allowDiagonal;
    bool allowSqueeze;
    Logger *logger;

    bool GetDataFromXml(TiXmlHandle);
};
#endif // ALGORITHM_H
