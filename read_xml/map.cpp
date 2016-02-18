#include "map.h"
#include "../tinyxml/tinyxml.h"

Map::Map()
{
    this->data = 0;
}

Map::Map(const char * fPath) {
    if(this->GetMapFromXML(fPath)) this->data = 1;
    else                           this->data = 0;
}

bool Map::GetMapFromXML(const char * fPath) {
    return true;
}

/* TO_DO
 *
 * class Map -> .h and .cpp
 * .h -> constructor
      destructor
      methods
      fields

    default constructor

    make file gl_const.h with defines for tags
    get <stringstream>
 */
