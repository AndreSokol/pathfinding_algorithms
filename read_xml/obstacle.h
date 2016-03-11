#ifndef OBSTACLE_H
#define OBSTACLE_H


class Obstacle
{
public:
    Obstacle();
private:
    int **columns;
    int columns_count;
    int perimeter;
    int area;
};

#endif // OBSTACLE_H
