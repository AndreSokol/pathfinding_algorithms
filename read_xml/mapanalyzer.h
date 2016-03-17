#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "gl_settings.h"

class MapAnalyzer
{
public:
    MapAnalyzer(Map *);
    ~MapAnalyzer();

    friend std::ostream& operator<< (std::ostream &, const MapAnalyzer &);

    int GetObstacleCount();
private:
    void AnalyzeMap();
    void FindObstacles();
    void CalculateOverallArea();
    void CalculateOverallPerimeter();
    void CalculateDensity();
    void CalculateAverageArea();
    void CalculateAveragePerimeter();
    void CalculateAreaDispersion();
    double CalculatePerimeterDispersion();

    void BreadthFirstSearch(bool **, int, int, std::vector<Utils::Coords> &);

    int overallArea;
    double density;
    double averageArea;
    int overallPerimeter;
    double averagePerimeter;
    double areaDispersion;
    double perimeterDispersion;
    Obstacle * obstacles;
    int obstacleCount;
    Map * map;
};

#endif // ANALYSIS_H
