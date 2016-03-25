#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "gl_settings.h"

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
private:
    Utils::ObstacleRow * _rows;
    int _rowsCount;
    int _perimeter;
    int _area;

    int calculatePerimeter();
    void calculateArea();
};

#endif // OBSTACLE_H
