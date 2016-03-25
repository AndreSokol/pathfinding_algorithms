#include "mapanalyzer.h"
#include "gl_settings.h"

MapAnalyzer::MapAnalyzer(Map * mapToAnalyze)
{
    this->occupiedArea = 0;
    this->occupationDensity = 0.0;
    this->averageObstacleArea = 0.0;
    this->overallObstaclesPerimeter = 0;
    this->averageObstaclePerimeter = 0.0;
    this->obstaclesAreaDispersion = 0.0;
    this->obstaclesPerimeterDispersion = 0.0;
    this->obstacles = NULL;
    this->obstacleCount = 0;
    this->map = mapToAnalyze;
    this->AnalyzeMap();
}

MapAnalyzer::~MapAnalyzer() {
    delete [] this->obstacles;
}

void MapAnalyzer::AnalyzeMap() {
    this->FindObstacles();
    this->CalculateOccupiedArea();
    this->CalculateOverallPerimeter();
    this->CalculateDensity();
    this->CalculateAverageArea();
    this->CalculateAveragePerimeter();
    this->CalculateAreaDispersion();
}

void MapAnalyzer::CalculateOccupiedArea() {
    int answer = 0;
    for(int i = 0; i < this->obstacleCount; i++) {
        answer += this->obstacles[i].area();
    }
    this->occupiedArea = answer;
}

void MapAnalyzer::CalculateDensity()  {
    this->occupationDensity = double(this->occupiedArea) / double(this->map->GetMapArea());
}

void MapAnalyzer::FindObstacles()  {
    bool ** visited = new bool * [this->map->GetHeight()];
    for(int i = 0; i < this->map->GetHeight(); i++) {
        visited[i] = new bool [this->map->GetWidth()];
        for(int j = 0; j < this->map->GetWidth(); j++)
            visited[i][j] = false;
    }

    std::vector<Utils::Coords> obstacleCoord;
    std::vector<Obstacle> obstacleCompressed;


    for(int i = 0; i < this->map->GetHeight(); ++i) {
        for(int j = 0; j < this->map->GetWidth(); ++j) {
            if (!visited[i][j] && this->map->At(i, j) != 0) {
                obstacleCoord.clear();
                this->BreadthFirstSearch(visited, i, j, obstacleCoord);
                std::sort(obstacleCoord.begin(), obstacleCoord.end(), Utils::CoordsComparator);

                // See Utils::ObstacleRow definition about compressing
                Obstacle newObstacle = Obstacle(obstacleCoord);
                obstacleCompressed.push_back(newObstacle);
            }
        }
    }

    this->obstacleCount = obstacleCompressed.size();
    this->obstacles = new Obstacle [this->obstacleCount];
    for (int i = 0; i < this->obstacleCount; ++i) {
        this->obstacles[i] = obstacleCompressed[i];
    }

    for (int i = 0; i < this->map->GetHeight(); i++) {
        delete [] visited[i];
    }

    delete [] visited;
}

void MapAnalyzer::BreadthFirstSearch(bool ** visited,
                                  int startx,
                                  int starty,
                                  std::vector<Utils::Coords> & coords) {
    std::queue<Utils::Coords> queue;
    queue.push(Utils::Coords(startx, starty));
    while(queue.size() > 0) {
        Utils::Coords currentCoords = queue.front();
        queue.pop();
        coords.push_back(currentCoords);
        visited[currentCoords.x][currentCoords.y] = true;

        if (this->map->At(currentCoords.x + 1, currentCoords.y) != 0 &&
            this->map->At(currentCoords.x + 1, currentCoords.y) != ELEMENT_OUT_OF_GRID ) {
            if(!visited[currentCoords.x + 1][currentCoords.y]) {
                queue.push(Utils::Coords(currentCoords.x + 1, currentCoords.y));
            }
        }

        if (this->map->At(currentCoords.x - 1, currentCoords.y) != 0 &&
            this->map->At(currentCoords.x - 1, currentCoords.y) != ELEMENT_OUT_OF_GRID ) {
            if (!visited[currentCoords.x - 1][currentCoords.y]) {
                queue.push(Utils::Coords(currentCoords.x - 1, currentCoords.y));
            }
        }

        if (this->map->At(currentCoords.x, currentCoords.y + 1) != 0 &&
            this->map->At(currentCoords.x, currentCoords.y + 1) != ELEMENT_OUT_OF_GRID ) {
            if (!visited[currentCoords.x][currentCoords.y + 1]) {
                queue.push(Utils::Coords(currentCoords.x, currentCoords.y + 1));
            }
        }

        if (this->map->At(currentCoords.x, currentCoords.y - 1) != 0 &&
            this->map->At(currentCoords.x, currentCoords.y - 1) != ELEMENT_OUT_OF_GRID ) {
            if (!visited[currentCoords.x][currentCoords.y - 1]) {
                queue.push(Utils::Coords(currentCoords.x, currentCoords.y - 1));
            }
        }
    }

    /*
     * Here must be queue reallocating, but since I've got some problems with C++11,
     * so can't do it like with vector in Utils::reallocateVector()
     */
}

void MapAnalyzer::CalculateAverageArea()  {
    this->averageObstacleArea = double(this->occupiedArea) / double(this->obstacleCount);
}

void MapAnalyzer::CalculateOverallPerimeter()  {
    int answer = 0;
    for (int i = 0; i < this->map->GetHeight(); i++) {
        for (int j = 0; j < map->GetWidth(); j++) {
            if (this->map->At(i, j) == 1) {
                if (this->map->At(i - 1, j) == 0) answer++;
                if (this->map->At(i + 1, j) == 0) answer++;
                if (this->map->At(i, j - 1) == 0) answer++;
                if (this->map->At(i, j + 1) == 0) answer++;
            }
        }
    }
    this->overallObstaclesPerimeter = answer;
}

void MapAnalyzer::CalculateAveragePerimeter()  {
    this->averageObstaclePerimeter = double(this->overallObstaclesPerimeter) / double(this->obstacleCount);
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
    return this->obstacleCount;
}
