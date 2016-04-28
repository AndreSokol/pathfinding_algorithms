#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "gl_settings.h"

class MapAnalyzer
{
public:
    MapAnalyzer(Map *, Logger *);
    ~MapAnalyzer();

    friend std::ostream& operator<< (std::ostream &, const MapAnalyzer &);

    int GetObstacleCount();
    TiXmlElement* DumpToXmlElement();
private:
    void AnalyzeMap();
    void FindObstacles();
    void CalculateOccupiedArea();
    void CalculateOverallPerimeter();
    void CalculateDensity();
    void CalculateAverageArea();
    void CalculateAveragePerimeter();
    void CalculateAreaDispersion();
    void CalculatePerimeterDispersion();

    void BreadthFirstSearch(std::set<Utils::Coords> &, Utils::Coords, std::vector<Utils::Coords> &);

    int occupiedArea;
    double occupationDensity;
    double averageObstacleArea;
    int overallObstaclesPerimeter;
    double averageObstaclePerimeter;
    double obstaclesAreaDispersion;
    double obstaclesPerimeterDispersion;
    Obstacle * obstacles;
    int obstacleCount;
    Map * map;
    Logger *logger;
};

#endif // ANALYSIS_H
