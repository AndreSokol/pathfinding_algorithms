#include "utils.h"
#include "gl_settings.h"

namespace Utils {
template <typename Type>
std::string toString(const Type& element) {
    std::stringstream sstream;
    sstream << element;
    return sstream.str();
}

template <typename Type>
void ReportTagMissing(const std::string & tag, const Type & default_value) {
    std::cerr << "[WARNING] Tag <" << tag << "> is missing; default value '" << default_value << "' set." << std::endl;
}

template<typename Type>
void reallocateVector(std::vector<Type> & v) {
    std::vector<Type>().swap(v);
}

inline bool CoordsComparator(const Coords & a, const Coords & b) {
    if (a.x == b.x) return a.y < b.y;
    else return a.x < b.x;
}

Coords::Coords(const int & a, const int & b) {
    this->x = a;
    this->y = b;
}

Coords Coords::operator+(const Coords & other) {
    return Coords(this->x + other.x, this->y + other.y);
}
}
