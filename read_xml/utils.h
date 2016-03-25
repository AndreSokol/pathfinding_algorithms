#ifndef UTILS_H
#define UTILS_H

namespace Utils {

template <typename Type>
std::string toString(const Type &);

template <typename Type>
void ReportTagMissing(const std::string &, const Type &);

/*
 * We store obstacle as an array of solid lines, called ObstacleRow's.
 * Each sequence of cells in one rows compresses to one object, describing by row number(x) and
 * first and last cell coordinates (y1 and y2) and a number of line (x)
 */
struct ObstacleRow {
    int x;
    int y1, y2;
};

struct Coords {
    Coords(const int &, const int &);
    int x;
    int y;
    Coords operator+(const Coords &);
};

inline bool CoordsComparator (const Coords &, const Coords &);

template<typename Type>
void reallocateVector(std::vector<Type> &);


/* Some const arrays to come round all neighbors in a pretty way */
const Coords NEIGHBOURS_NO_DIAG[4] = {Coords(1, 0),
                                      Coords(0, 1),
                                      Coords(-1, 0),
                                      Coords(0, -1)};

const Coords NEIGHBOURS_DIAG[8] = {Coords(-1, -1), Coords(-1, 0), Coords(-1, 1),
                                   Coords(0, -1),                 Coords(0, 1),
                                   Coords(1, -1),  Coords(1, 0),  Coords(1, 1)};

}
#endif // UTILS_H
