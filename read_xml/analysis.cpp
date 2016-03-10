#include "analysis.h"
#include "gl_settings.h"

Analysis::Analysis()
{
}

void Analysis::AnalyzeMap(Map * map) {
    this->overallArea = CalculateObstacleArea(map);
    this->density = CalculateDensity(map);
    this->overallPerimeter = CalculateOverallPerimeter(map);
}

int Analysis::CalculateObstacleArea(Map * map) {
    int answer = 0;
    for(int i = 0; i < map->GetHeight(); i++) {
        for(int j = 0; j < map->GetWidth(); j++) {
            if (map->At(i, j) != 0) answer++;
        }
    }
    return answer;
}

double Analysis::CalculateDensity(Map * map)  {
    double answer = (double) this->overallArea;
    return answer / map->GetMapArea();
}

int Analysis::CalculateObstaclesCount(Map * map)  {
    // TO BE IMPLEMENTED
}

double Analysis::CalculateAverageObstacleArea(Map * map)  {
    // TO BE IMPLEMENTED
}

int Analysis::CalculateOverallPerimeter(Map * map)  {
    int answer = 0;
    for (int i = 0; i < map->GetHeight(); i++) {
        for (int j = 0; j < map->GetWidth(); j++) {
            if (map->At(i, j) == 1) {
                if (map->At(i - 1, j) == 0) answer++;
                if (map->At(i + 1, j) == 0) answer++;
                if (map->At(i, j - 1) == 0) answer++;
                if (map->At(i, j + 1) == 0) answer++;
            }
        }
    }
    return answer;
}

double Analysis::CalculateAveragePerimeter(Map * map)  {
    // TO BE IMPLEMENTED
}

double Analysis::CalculateAreaDispersion(Map * map)  {
    // TO BE IMPLEMENTED
}

double Analysis::CalculatePerimeterDispersion(Map * map)  {
    // TO BE IMPLEMENTED
}

std::ostream& operator<< (std::ostream & os, const Analysis & a) {
    os << "Analysis results:" << std::endl;
    os << "Density " << a.density << std::endl;
    os << "Overall area " << a.overallArea << std::endl;
    os << "Overall primeter " << a.overallPerimeter << std::endl;
    return os;
}
