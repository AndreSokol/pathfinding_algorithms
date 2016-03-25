#include "obstacle.h"

Obstacle::Obstacle() {
    this->_area = 0;
    this->_perimeter = 0;
    this->_rowsCount = 0;
    this->_rows = NULL;
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

    this->_rowsCount = compressedV.size();

    this->_rows = new Utils::ObstacleRow[this->_rowsCount];

    for (int i = 0; i < this->_rowsCount; ++i) {
        this->_rows[i] = compressedV[i];
    }

    Utils::reallocateVector(compressedV);

    this->calculateArea();
    this->_perimeter = this->calculatePerimeter();
}

Obstacle::~Obstacle() {
    delete [] this->_rows;
}

Obstacle& Obstacle::operator= (const Obstacle &other) {
    this->_area = other._area;
    this->_perimeter = other._perimeter;
    this->_rowsCount = other._rowsCount;
    this->_rows = new Utils::ObstacleRow[this->_rowsCount];
    for(int i = 0; i < this->_rowsCount; ++i) {
        this->_rows[i] = other._rows[i];
    }
}

int Obstacle::size() {
    return this->_rowsCount;
}

int Obstacle::area() {
    return this->_area;
}

int Obstacle::perimeter() {
    return this->_perimeter;
}

void Obstacle::calculateArea() {
    int ans = 0;
    for (int i = 0; i < this->_rowsCount; i++)
        ans += this->_rows[i].y2 - this->_rows[i].y1 + 1;
    this->_area = ans;
}

int Obstacle::calculatePerimeter() {
    /*
     * TO BE IMPLEMENTED
     */
    return 0;
}
