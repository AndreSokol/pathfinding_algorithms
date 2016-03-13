#include "analysis.h"
#include "gl_settings.h"

Analysis::Analysis()
{
    this->overallArea = 0;
    this->density = 0.0;
    this->averageArea = 0.0;
    this->overallPerimeter = 0;
    this->averagePerimeter = 0.0;
    this->areaDispersion = 0.0;
    this->perimeterDispersion = 0.0;
    this->obstacles = NULL;
    this->obstacleCount = 0;
}

Analysis::~Analysis() {
    delete [] this->obstacles;
}

void Analysis::AnalyzeMap(Map * map) {
    this->FindObstacles(map);
    this->CalculateOverallArea();
    this->CalculateOverallPerimeter(map);
    this->CalculateDensity(map);
    this->CalculateAverageArea();
    this->CalculateAveragePerimeter();
    this->CalculateAreaDispersion();
}

void Analysis::CalculateOverallArea() {
    int answer = 0;
    for(int i = 0; i < this->obstacleCount; i++) {
        answer += this->obstacles[i].area();
    }
    this->overallArea = answer;
}

void Analysis::CalculateDensity(Map * map)  {
    this->density = double(this->overallArea) / double(map->GetMapArea());
}

void Analysis::FindObstacles(Map * map)  {
    bool ** visited = new bool * [map->GetHeight()];
    for(int i = 0; i < map->GetHeight(); i++) {
        visited[i] = new bool [map->GetWidth()];
        for(int j = 0; j < map->GetWidth(); j++)
            visited[i][j] = false;
    }

    std::vector<Utils::Coords> obstacleCoord;
    std::vector<Obstacle> obstacleCompressed;


    for(int i = 0; i < map->GetHeight(); ++i) {
        for(int j = 0; j < map->GetWidth(); ++j) {
            if (!visited[i][j] && map->At(i, j) != 0) {
                obstacleCoord.clear();
                this->BreadthFirstSearch(visited, i, j, obstacleCoord, map);
                std::sort(obstacleCoord.begin(), obstacleCoord.end(), Utils::CoordsComparator);

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

    for (int i = 0; i < map->GetHeight(); i++) {
        delete [] visited[i];
    }

    delete [] visited;
}

void Analysis::BreadthFirstSearch(bool ** visited,
                                  int startx,
                                  int starty,
                                  std::vector<Utils::Coords> & coords,
                                  Map * map) {
    std::queue<Utils::Coords> queue;
    queue.push(Utils::Coords(startx, starty));
    while(queue.size() > 0) {
        Utils::Coords currentCoords = queue.front();
        queue.pop();
        coords.push_back(currentCoords);
        visited[currentCoords.x][currentCoords.y] = true;

        if (map->At(currentCoords.x + 1, currentCoords.y) != 0 &&
            map->At(currentCoords.x + 1, currentCoords.y) != ELEMENT_OUT_OF_GRID ) {
            if(!visited[currentCoords.x + 1][currentCoords.y]) {
                queue.push(Utils::Coords(currentCoords.x + 1, currentCoords.y));
            }
        }

        if (map->At(currentCoords.x - 1, currentCoords.y) != 0 &&
            map->At(currentCoords.x - 1, currentCoords.y) != ELEMENT_OUT_OF_GRID ) {
            if (!visited[currentCoords.x - 1][currentCoords.y]) {
                queue.push(Utils::Coords(currentCoords.x - 1, currentCoords.y));
            }
        }

        if (map->At(currentCoords.x, currentCoords.y + 1) != 0 &&
            map->At(currentCoords.x, currentCoords.y + 1) != ELEMENT_OUT_OF_GRID ) {
            if (!visited[currentCoords.x][currentCoords.y + 1]) {
                queue.push(Utils::Coords(currentCoords.x, currentCoords.y + 1));
            }
        }

        if (map->At(currentCoords.x, currentCoords.y - 1) != 0 &&
            map->At(currentCoords.x, currentCoords.y - 1) != ELEMENT_OUT_OF_GRID ) {
            if (!visited[currentCoords.x][currentCoords.y - 1]) {
                queue.push(Utils::Coords(currentCoords.x, currentCoords.y - 1));
            }
        }
    }

    /*
     * Here must be queue reallocating, but I've got some problems with C++11,
     * so can't do it like with vector in Utils::reallocateVector()
     */
}

void Analysis::CalculateAverageArea()  {
    this->averageArea = double(this->overallArea) / double(this->obstacleCount);
}

void Analysis::CalculateOverallPerimeter(Map * map)  {
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
    this->overallPerimeter = answer;
}

void Analysis::CalculateAveragePerimeter()  {
    this->averagePerimeter = double(this->overallPerimeter) / double(this->obstacleCount);
}

void Analysis::CalculateAreaDispersion()  {
    if (this->obstacleCount < 2) return;
    double ans = 0.0;
    for (int i = 0; i < this->obstacleCount; i++) {
        ans += (this->obstacles[i].area() - this->averageArea) * (this->obstacles[i].area() - this->averageArea);
    }
    this->areaDispersion = ans / double(this->obstacleCount - 1);
}

double Analysis::CalculatePerimeterDispersion(Map * map)  {
    // TO BE IMPLEMENTED
    return 0;
}

std::ostream& operator<< (std::ostream & os, const Analysis & a) {
    os << "Analysis results:" << std::endl;
    os << "Density " << a.density << std::endl;
    os << "Found " << a.obstacleCount << " obstacles" << std::endl;
    os << "Overall area " << a.overallArea << std::endl;
    os << "Average area " << a.averageArea << std::endl;
    os << "Area dispersion " << a.areaDispersion << std::endl;
    os << "Overall perimeter " << a.overallPerimeter << std::endl;
    os << "Average perimeter " << a.averagePerimeter << std::endl;

    return os;
}

int Analysis::GetObstacleCount() {
    return this->obstacleCount;
}
