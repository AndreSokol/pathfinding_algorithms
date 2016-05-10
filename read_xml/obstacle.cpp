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
    calculatePerimeter();
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

void Obstacle::calculatePerimeter() {
    std::set<int> previous_line;
    std::set<int> current_line;
    int perimeter = 0;

    int current_line_num = _rows[0].x;
    Utils::ObstacleRow current_row;

    for (int i = 0; i < _rowsCount; i++) {
        current_row = _rows[i];

        if(current_row.x != current_line_num) {
            // if we get to the end of the line, we need to check for adjacent cells

            std::set<int>::iterator it = current_line.begin();
            for(; it != current_line.end(); it++) {
                if(previous_line.find(*it) != previous_line.end()) {
                    // if element is found in previous line we've got 2 adjacent cells
                    // and 1 edge of each is not outer
                    perimeter -= 2;
                }
            }
            previous_line = current_line;
            current_line.clear();
            current_line_num++;
        }

        // Adding row to the current line
        perimeter += 2; // small sides of the row
        perimeter += (current_row.y2 - current_row.y1 + 1) * 2; // big sides of the row
        for (int j = current_row.y1; j <= current_row.y2; j++) {
            current_line.insert(j); // adding cells to current_line set
        }

    }

    // checking adjacents for last line
    std::set<int>::iterator it = current_line.begin();
    for(; it != current_line.end(); it++) {
        if(previous_line.find(*it) != previous_line.end()) {
            // if element is found in previous line we've got 2 adjacent cells
            // and 1 edge of each is not outer
            perimeter -= 2;
        }
    }

    _perimeter = perimeter;

    /*
     * delete sets here
     */
}

TiXmlElement* Obstacle::DumpToXmlElement(int number) {
    TiXmlElement * root = new TiXmlElement( TAG_ANAlYSIS_OBSTACLE );
    root->SetAttribute( ATTRIBUTE_OBSTACLE_NUMBER, Utils::toString(number) );
    root->SetAttribute( ATTRIBUTE_OBSTACLE_PERIMETER, Utils::toString(_perimeter) );
    root->SetAttribute( ATTRIBUTE_OBSTACLE_AREA, Utils::toString(_area) );

    return root;
}
