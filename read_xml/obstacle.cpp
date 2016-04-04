#include "obstacle.h"

Obstacle::Obstacle() {
    _area = 0;
    _perimeter = 0;
    _rowsCount = 0;
    _rows = NULL;
}

Obstacle::Obstacle(const std::vector<Utils::Coords> & v)
{
    // See Utils::ObstacleRow definition about compressing
    std::vector<Utils::ObstacleRow> compressedV;
    Utils::ObstacleRow newRow;
    newRow.x = v[0].x;
    newRow.y1 = v[0].y;
    newRow.y2 = v[0].y;
    for (unsigned int i = 0; i < v.size(); ++i) {
        if (newRow.x != v[i].x) {
            compressedV.push_back(newRow);
            newRow.x = v[i].x;
            newRow.y1 = v[i].y;
            newRow.y2 = v[i].y;
        }
        else {
            newRow.y2 = v[i].y;
        }
    }
    compressedV.push_back(newRow);

    _rowsCount = compressedV.size();

    _rows = new Utils::ObstacleRow[_rowsCount];

    for (int i = 0; i < _rowsCount; ++i) {
        _rows[i] = compressedV[i];
    }

    Utils::reallocateVector(compressedV);

    calculateArea();
    _perimeter = calculatePerimeter();
}

Obstacle::~Obstacle() {
    delete [] _rows;
}

Obstacle& Obstacle::operator= (const Obstacle &other) {
    _area = other._area;
    _perimeter = other._perimeter;
    _rowsCount = other._rowsCount;
    _rows = new Utils::ObstacleRow[_rowsCount];
    for(int i = 0; i < _rowsCount; ++i) {
        _rows[i] = other._rows[i];
    }
    return *this;
}

int Obstacle::size() {
    return _rowsCount;
}

int Obstacle::area() {
    return _area;
}

int Obstacle::perimeter() {
    return _perimeter;
}

void Obstacle::calculateArea() {
    int ans = 0;
    for (int i = 0; i < _rowsCount; i++)
        ans += _rows[i].y2 - _rows[i].y1 + 1;
    _area = ans;
}

int Obstacle::calculatePerimeter() {
    /*
     * TO BE IMPLEMENTED
     */
    return 0;
}
