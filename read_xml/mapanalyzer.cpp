#include "mapanalyzer.h"
#include "gl_settings.h"

MapAnalyzer::MapAnalyzer(Map * mapToAnalyze, Logger * logger)
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
    this->logger = logger;

    AnalyzeMap();
}

MapAnalyzer::~MapAnalyzer() {
    //delete [] obstacles;
}

void MapAnalyzer::AnalyzeMap() {
    FindObstacles();
    CalculateOccupiedArea();
    CalculateOverallPerimeter();
    CalculateDensity();
    CalculateAverageArea();
    CalculateAveragePerimeter();
    CalculateAreaDispersion();
    CalculatePerimeterDispersion();
}

void MapAnalyzer::CalculateOccupiedArea() {
    *logger << "[INFO] Calculating area...";

    int answer = 0;
    for(int i = 0; i < obstacleCount; i++) {
        answer += obstacles[i].area();
    }
    occupiedArea = answer;

    *logger << " result is " << occupiedArea << "!" << std::endl;
}

void MapAnalyzer::CalculateDensity()  {
    *logger << "[INFO] Calculating density...";
    occupationDensity = double(occupiedArea) / double(map->GetMapArea());
    *logger << " result is " << occupationDensity << "!" << std::endl;
}

void MapAnalyzer::FindObstacles()  {
    *logger << "[INFO] Searching obstacles..." << std::endl;

    std::set<Utils::Coords> visited;

    std::vector<Utils::Coords> obstacleCoord;
    std::vector<Obstacle> obstacleCompressed;

    Utils::Coords currentCoords = Utils::Coords(0, 0);
    for(int i = 0; i < map->GetHeight(); ++i) {
        for(int j = 0; j < map->GetWidth(); ++j) {
            currentCoords = Utils::Coords(i, j);
            if (visited.find(currentCoords) == visited.end() &&
                    map->At(currentCoords) != INPUT_FREE_CELL) {
                BreadthFirstSearch(visited, currentCoords, obstacleCoord);
                std::sort(obstacleCoord.begin(), obstacleCoord.end());

                // See Utils::ObstacleRow definition about compressing
                Obstacle newObstacle = Obstacle(obstacleCoord);
                obstacleCompressed.push_back(newObstacle);
                *logger << "[INFO] " << (i * map->GetWidth() + j) * 100.0 / map->GetMapArea() << "% of map analysed..." << std::endl;
                Utils::reallocateVector(obstacleCoord);
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


    *logger << "[INFO] 100% of map analysed: " << obstacleCount << " obstacles found!" << std::endl;
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
            if (map->At(coordsToCheck) != INPUT_FREE_CELL &&
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
    *logger << "[INFO] Calculating average obstacles area...";
    averageObstacleArea = double(occupiedArea) / double(obstacleCount);
    *logger << " result is " << averageObstacleArea << "!" << std::endl;
}

void MapAnalyzer::CalculateOverallPerimeter()  {
    *logger << "[INFO] Calculating overall perimeter...";
    int answer = 0;
    for(int i = 0; i < obstacleCount; i++)
        answer += obstacles[i].perimeter();
    overallObstaclesPerimeter = answer;
    *logger << " result is " << overallObstaclesPerimeter << "!" << std::endl;
}

void MapAnalyzer::CalculateAveragePerimeter()  {
    *logger << "[INFO] Calculating average obstacle perimeter...";
    averageObstaclePerimeter = double(overallObstaclesPerimeter) / double(obstacleCount);
    *logger << " result is " << averageObstaclePerimeter << "!" << std::endl;
}

void MapAnalyzer::CalculateAreaDispersion()  {
    *logger << "[INFO] Calculating obstacle area dispersion...";
    if (obstacleCount >= 2) {
        double ans = 0.0;
        for (int i = 0; i < obstacleCount; i++) {
            ans += (obstacles[i].area() - averageObstacleArea) *
                     (obstacles[i].area() - averageObstacleArea);
        }

        obstaclesAreaDispersion = ans / double(obstacleCount - 1);
    }
    *logger << " result is " << obstaclesAreaDispersion << "!" << std::endl;
}

void MapAnalyzer::CalculatePerimeterDispersion()  {
    *logger << "[INFO] Calculating obstacle perimeter dispersion...";
    if (obstacleCount >= 2) {
        double ans = 0.0;
        for (int i = 0; i < obstacleCount; i++) {
            ans += (obstacles[i].perimeter() - averageObstaclePerimeter) *
                             (obstacles[i].perimeter() - averageObstaclePerimeter);
        }
        obstaclesPerimeterDispersion = ans / double(obstacleCount - 1);
    }
    *logger << " result is " << obstaclesPerimeterDispersion << "!" << std::endl;
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
    os << "Perimeter dispersion " << a.obstaclesPerimeterDispersion << std::endl;

    return os;
}

int MapAnalyzer::GetObstacleCount() {
    return obstacleCount;
}

TiXmlElement* MapAnalyzer::DumpToXmlElement(int logLevel) {
    *logger << "[INFO] Dumping analysis results to XML..." << std::endl;
    TiXmlElement* root = new TiXmlElement( TAG_ANALYSIS_CONTAINER );

    *logger << "[INFO] Dumping obstacles summary to XML..." << std::endl;
    TiXmlElement* summary = new TiXmlElement( TAG_ANALYSIS_SUMMARY );
    summary->LinkEndChild(Utils::dumpValueToXmlNode(obstacleCount, TAG_ANALYSIS_OBSTACLE_COUNT));
    summary->LinkEndChild(Utils::dumpValueToXmlNode(occupationDensity, TAG_ANALYSIS_OCCUPATION_DENSITY));
    summary->LinkEndChild(Utils::dumpValueToXmlNode(occupiedArea, TAG_ANALYSIS_TOTAL_OBSTACLE_AREA));
    summary->LinkEndChild(Utils::dumpValueToXmlNode(overallObstaclesPerimeter, TAG_ANALYSIS_TOTAL_OBSTACLE_PERIMETER));
    summary->LinkEndChild(Utils::dumpValueToXmlNode(averageObstacleArea, TAG_ANALYSIS_AVERAGE_OBSTACLE_AREA));
    summary->LinkEndChild(Utils::dumpValueToXmlNode(averageObstaclePerimeter, TAG_ANALYSIS_AVERAGE_OBSTACLE_PERIMETER));
    summary->LinkEndChild(Utils::dumpValueToXmlNode(obstaclesAreaDispersion, TAG_ANALYSIS_OBSTACLE_AREA_DISPERSION));
    summary->LinkEndChild(Utils::dumpValueToXmlNode(obstaclesPerimeterDispersion, TAG_ANALYSIS_OBSTACLE_PERIMETER_DISPERSION));
    root->LinkEndChild(summary);
    *logger << "[INFO] Dumping obstacles summary to XML done!" << std::endl;

    if (logLevel == 1) {
        *logger << "[INFO] Log level set to 1, do not dumping list of obstacles" << std::endl;
    }
    else {
        *logger << "[INFO] Dumping list of obstacles (log level set to " << logLevel << ")..." << std::endl;
        TiXmlElement * obstacleList = new TiXmlElement( TAG_ANALYSIS_OBSTACLE_CONTAINER );
        for (int i = 0; i < obstacleCount; i++) obstacleList->LinkEndChild( obstacles[i].DumpToXmlElement(i) );
        root->LinkEndChild(obstacleList);
        *logger << "[INFO] Dumping list of obstacles done!" << std::endl;
    }

    *logger << "[INFO] Dumping analysis results to XML done!" << std::endl;
    return root;
}
