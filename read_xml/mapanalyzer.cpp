#include "mapanalyzer.h"
#include "gl_settings.h"

MapAnalyzer::MapAnalyzer(Map * mapToAnalyze)
{
    occupiedArea = 0;
    occupationDensity = 0.0;
    averageObstacleArea = 0.0;
    overallObstaclesPerimeter = 0;
    averageObstaclePerimeter = 0.0;
    obstaclesAreaDispersion = 0.0;
    obstaclesPerimeterDispersion = 0.0;
    obstacles = NULL;
    obstacleCount = 0;
    map = mapToAnalyze;

    AnalyzeMap();
}

MapAnalyzer::~MapAnalyzer() {
    delete [] obstacles;
}

void MapAnalyzer::AnalyzeMap() {
    FindObstacles();
    CalculateOccupiedArea();
    CalculateOverallPerimeter();
    CalculateDensity();
    CalculateAverageArea();
    CalculateAveragePerimeter();
    CalculateAreaDispersion();
}

void MapAnalyzer::CalculateOccupiedArea() {
    int answer = 0;
    for(int i = 0; i < obstacleCount; i++) {
        answer += obstacles[i].area();
    }
    occupiedArea = answer;
}

void MapAnalyzer::CalculateDensity()  {
    occupationDensity = double(occupiedArea) / double(map->GetMapArea());
}

void MapAnalyzer::FindObstacles()  {
    std::set<Utils::Coords> visited;

    std::vector<Utils::Coords> obstacleCoord;
    std::vector<Obstacle> obstacleCompressed;

    Utils::Coords currentCoords = Utils::Coords(0, 0);
    for(int i = 0; i < map->GetHeight(); ++i) {
        for(int j = 0; j < map->GetWidth(); ++j) {
            currentCoords = Utils::Coords(i, j);
            if (visited.find(currentCoords) == visited.end() &&
                    map->At(currentCoords) != 0) {
                BreadthFirstSearch(visited, currentCoords, obstacleCoord);
                std::sort(obstacleCoord.begin(), obstacleCoord.end());

                // See Utils::ObstacleRow definition about compressing
                Obstacle newObstacle = Obstacle(obstacleCoord);
                obstacleCompressed.push_back(newObstacle);

                obstacleCoord.clear();
            }
        }
    }

    obstacleCount = obstacleCompressed.size();
    obstacles = new Obstacle [obstacleCount];
    for (int i = 0; i < obstacleCount; ++i) {
        obstacles[i] = obstacleCompressed[i];
    }

    Utils::reallocateVector(obstacleCoord);
    Utils::reallocateVector(obstacleCompressed);
}

void MapAnalyzer::BreadthFirstSearch(std::set<Utils::Coords> & visited,
                                  Utils::Coords startCoords,
                                  std::vector<Utils::Coords> & coords) {
    std::queue<Utils::Coords> queue;
    queue.push(startCoords);

    while(queue.size() > 0) {
        Utils::Coords currentCoords = queue.front();
        queue.pop();
        coords.push_back(currentCoords);
        visited.insert(currentCoords);

        for(int i = 0; i < 4; i++) {
            Utils::Coords coordsToCheck = currentCoords + Utils::NEIGHBOURS_NO_DIAG[i];
            if (map->At(coordsToCheck) != 0 &&
                map->At(coordsToCheck) != ELEMENT_OUT_OF_GRID ) {
                if(visited.count(coordsToCheck) == 0) {
                    queue.push(coordsToCheck);
                }
            }
        }
    }

    /*
     * Here must be queue reallocating, but since I've got some problems with C++11,
     * so can't do it like with vector in Utils::reallocateVector()
     */
}

void MapAnalyzer::CalculateAverageArea()  {
    averageObstacleArea = double(occupiedArea) / double(obstacleCount);
}

void MapAnalyzer::CalculateOverallPerimeter()  {
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
    overallObstaclesPerimeter = answer;
}

void MapAnalyzer::CalculateAveragePerimeter()  {
    averageObstaclePerimeter = double(overallObstaclesPerimeter) / double(obstacleCount);
}

void MapAnalyzer::CalculateAreaDispersion()  {
    if (this->obstacleCount < 2) return;
    double ans = 0.0;
    for (int i = 0; i < this->obstacleCount; i++) {
        ans += (this->obstacles[i].area() - this->averageObstacleArea) * (this->obstacles[i].area() - this->averageObstacleArea);
    }
    this->obstaclesAreaDispersion = ans / double(this->obstacleCount - 1);
}

double MapAnalyzer::CalculatePerimeterDispersion()  {
    // TO BE IMPLEMENTED
    return 0;
}

std::ostream& operator<< (std::ostream & os, const MapAnalyzer & a) {
    os << "Analysis results:" << std::endl;
    os << "Density " << a.occupationDensity << std::endl;
    os << "Found " << a.obstacleCount << " obstacles" << std::endl;
    os << "Overall area " << a.occupiedArea << std::endl;
    os << "Average area " << a.averageObstacleArea << std::endl;
    os << "Area dispersion " << a.obstaclesAreaDispersion << std::endl;
    os << "Overall perimeter " << a.overallObstaclesPerimeter << std::endl;
    os << "Average perimeter " << a.averageObstaclePerimeter << std::endl;

    return os;
}

int MapAnalyzer::GetObstacleCount() {
    return obstacleCount;
}

TiXmlElement* MapAnalyzer::DumpToXmlElement() {
    TiXmlElement* root = new TiXmlElement( TAG_ANALYSIS_CONTAINER );

    TiXmlElement* obstacleCountEl = new TiXmlElement( TAG_ANALYSIS_OBSTACLE_COUNT );
    obstacleCountEl->LinkEndChild(new TiXmlText(Utils::toString(obstacleCount)));
    root->LinkEndChild(obstacleCountEl);

    TiXmlElement* densityEl = new TiXmlElement( TAG_ANALYSIS_OCCUPATION_DENSITY );
    densityEl->LinkEndChild(new TiXmlText(Utils::toString(occupationDensity)));
    root->LinkEndChild(densityEl);

    TiXmlElement* totalAreaEl = new TiXmlElement( TAG_ANALYSIS_TOTAL_OBSTACLE_AREA );
    totalAreaEl->LinkEndChild(new TiXmlText(Utils::toString(occupiedArea)));
    root->LinkEndChild(totalAreaEl);

    TiXmlElement* totalPerimeterEl = new TiXmlElement( TAG_ANALYSIS_TOTAL_OBSTACLE_PERIMETER );
    totalPerimeterEl->LinkEndChild(new TiXmlText(Utils::toString(overallObstaclesPerimeter)));
    root->LinkEndChild(totalPerimeterEl);

    TiXmlElement* averageAreaEl = new TiXmlElement( TAG_ANALYSIS_AVERAGE_OBSTACLE_AREA );
    averageAreaEl->LinkEndChild(new TiXmlText(Utils::toString(averageObstacleArea)));
    root->LinkEndChild(averageAreaEl);

    TiXmlElement* averagePerimeterEl = new TiXmlElement( TAG_ANALYSIS_AVERAGE_OBSTACLE_PERIMETER );
    averagePerimeterEl->LinkEndChild(new TiXmlText(Utils::toString(averageObstaclePerimeter)));
    root->LinkEndChild(averagePerimeterEl);

    TiXmlElement* areaDispersionEl = new TiXmlElement( TAG_ANALYSIS_OBSTACLE_AREA_DISPERSION );
    areaDispersionEl->LinkEndChild(new TiXmlText(Utils::toString(obstaclesAreaDispersion)));
    root->LinkEndChild(areaDispersionEl);

    /*TiXmlElement* perimeterDispersionEl = new TiXmlElement( TAG_ANALYSIS_OBSTACLE_PERIMETER_DISPERSION );
    perimeterDispersionEl->LinkEndChild(new TiXmlText(Utils::toString(obstaclesPerimeterDispersion)));
    root->LinkEndChild(perimeterDispersionEl);*/

    return root;
}
