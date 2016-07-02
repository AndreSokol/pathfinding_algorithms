#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "gl_settings.h"
#include "utils.h"

class Obstacle
{
public:
    Obstacle();
    Obstacle(const std::vector<Utils::Coords> &);
    ~Obstacle();

    Obstacle& operator= (const Obstacle &);

    int size();
    int area();
    int perimeter();

    TiXmlElement* DumpToXmlElement(int);
private:
    std::vector<Utils::ObstacleRow>  _rows;
    int _rowsCount;
    int _perimeter;
    int _area;

    void calculatePerimeter();
    void calculateArea();
};

#endif // OBSTACLE_H
