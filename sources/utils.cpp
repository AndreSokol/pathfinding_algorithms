#include "utils.h"
#include "errors.cpp"
#include "gl_settings.h"

namespace Utils {

void parseValueFromXmlNode(const TiXmlHandle & rootHandle, const char * tagName,
                           std::string & fieldToWrite, bool isObliged = false) {

    TiXmlElement* XmlElement = rootHandle.FirstChild( tagName ).ToElement();
    if(!XmlElement) {
        if (isObliged) throw MissingTagError( tagName );
        else           ReportTagMissing( tagName , fieldToWrite);
    } else {
        fieldToWrite = XmlElement->GetText();
    }
}

Coords::Coords() {
    x = 0;
    y = 0;
}

Coords::Coords(const int & a, const int & b) {
    this->x = a;
    this->y = b;
}

Coords Coords::operator+(const Coords & other) {
    return Coords(this->x + other.x, this->y + other.y);
}

bool operator==(const Coords &a, const Coords &b)
{
    return a.x == b.x && a.y == b.y;
}

bool operator!=(const Coords & a, const Coords & b)
{
    return !(a == b);
}

bool operator< (const Coords & a, const Coords & b) {
    if (a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

CoordsContainer::CoordsContainer() {
    coords = Coords();
    prev_coords = Coords();
    distance = 0;
}

CoordsContainer::CoordsContainer(Coords coords, Coords prev_coords, int distance) {
    this->coords = coords;
    this->prev_coords = prev_coords;
    this->distance = distance;
}

bool operator==(const CoordsContainer & a, const CoordsContainer & b)
{
    return a.coords == b.coords;
}

}
