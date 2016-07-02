#ifndef UTILS_H
#define UTILS_H

#include "gl_settings.h"
#include "errors.cpp"

namespace Utils {

template <typename Type>
void ReportTagMissing(const std::string & tag, const Type & default_value) {
    std::cerr << "[WARNING] Tag <" << tag << "> is missing; default value '" << default_value << "' set." << std::endl;
}


void parseValueFromXmlNode(const TiXmlHandle & rootHandle, const char * tagName,
                           std::string & fieldToWrite, bool isObliged);

template <typename Type>
void parseValueFromXmlNode(const TiXmlHandle & rootHandle, const char * tagName,
                           Type & fieldToWrite, bool isObliged = false) {

    TiXmlElement* XmlElement = rootHandle.FirstChild( tagName ).ToElement();
    if(!XmlElement) {
        if (isObliged) throw MissingTagError( tagName );
        else           ReportTagMissing( tagName , fieldToWrite);
    } else {
        std::istringstream(XmlElement->GetText()) >> fieldToWrite;
    }
}

template <typename Type>
std::string toString(const Type& element) {
    std::ostringstream sstream;
    sstream << element;
    return sstream.str();
}

template <typename Type>
TiXmlElement* dumpValueToXmlNode(const Type & value, const char * tagName) {
    TiXmlElement * node = new TiXmlElement( tagName );
    node->LinkEndChild(new TiXmlText( toString(value) ));
    return node;
}

template<typename Type>
void reallocateVector(std::vector<Type> & v) {
    std::vector<Type>().swap(v);
}


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
    Coords();
    Coords(const int &, const int &);
    int x;
    int y;
    Coords operator+(const Coords &);
};


struct CoordsContainer {
    CoordsContainer();
    CoordsContainer(Coords, Coords, int);
    Coords coords;
    Coords prev_coords;
    int distance;
};

bool operator==(const Coords &, const Coords &);
bool operator!=(const Coords &, const Coords &);
bool operator<(const Coords &, const Coords &);

bool operator==(const CoordsContainer &, const CoordsContainer &);

/* Some const arrays to come round all neighbors in a pretty way */
const Coords NEIGHBOURS_NO_DIAG[4] = {Coords(1, 0),
                                      Coords(0, 1),
                                      Coords(-1, 0),
                                      Coords(0, -1)};

const Coords NEIGHBOURS_DIAG[8] = {Coords(-1, -1), Coords(-1, 0), Coords(-1, 1),
                                   Coords(0, -1),                 Coords(0, 1),
                                   Coords(1, -1),  Coords(1, 0),  Coords(1, 1)};

}

/*
 * Need to define hash<Utils::Coords> in order to use unordered_map
 * Based on sample from cppreference.com
 */
namespace std {
    template<> struct hash<Utils::Coords> {
        std::size_t operator()(const Utils::Coords & coords) const
        {
            std::size_t h1 = std::hash<int>()(coords.x);
            std::size_t h2 = std::hash<int>()(coords.y);
            return h1 ^ (h2 << 1);
        }
    };
}

#endif // UTILS_H
