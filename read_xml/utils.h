#ifndef UTILS_H
#define UTILS_H

namespace Utils {

template <typename Type>
std::string toString(const Type &);

template <typename Type>
void ReportTagMissing(const std::string &, const Type &);

struct Row {
    int x;
    int y1, y2;
};

struct Coords {
    Coords(const int &, const int &);
    int x;
    int y;
};

inline bool CoordsComparator (const Coords &, const Coords &);

template<typename Type>
void reallocateVector(std::vector<Type> &);

}
#endif // UTILS_H
