#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "gl_settings.h"

class Analysis
{
public:
    Analysis();

    void AnalyzeMap(Map *);
    friend std::ostream& operator<< (std::ostream &, const Analysis &);
private:
    int CalculateObstacleArea(Map *);
    double CalculateDensity(Map *);
    int CalculateObstaclesCount(Map *);
    double CalculateAverageObstacleArea(Map *);
    int CalculateOverallPerimeter(Map *);
    double CalculateAveragePerimeter(Map *);
    double CalculateAreaDispersion(Map *);
    double CalculatePerimeterDispersion(Map *);

    int overallArea;
    double density;
    int obstacleCount;
    double averageArea;
    int overallPerimeter;
    double averagePerimeter;
    double areaDispersion;
    double perimeterDispersion;
};

#endif // ANALYSIS_H
