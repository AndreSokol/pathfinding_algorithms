#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "gl_settings.h"

class Analysis
{
public:
    Analysis();
    ~Analysis();

    void AnalyzeMap(Map *);
    friend std::ostream& operator<< (std::ostream &, const Analysis &);

    int GetObstacleCount();
private:
    void FindObstacles(Map *);
    void CalculateOverallArea();
    void CalculateOverallPerimeter(Map *);
    void CalculateDensity(Map *);
    void CalculateAverageArea();
    void CalculateAveragePerimeter();
    void CalculateAreaDispersion();
    double CalculatePerimeterDispersion(Map *);

    void BreadthFirstSearch(bool **, int, int, std::vector<Utils::Coords> &, Map *);

    int overallArea;
    double density;
    double averageArea;
    int overallPerimeter;
    double averagePerimeter;
    double areaDispersion;
    double perimeterDispersion;
    Obstacle * obstacles;
    int obstacleCount;
};

#endif // ANALYSIS_H
