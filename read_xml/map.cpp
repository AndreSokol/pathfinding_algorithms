#include "map.h"
#include "utils.h"
#include "gl_settings.h"

Map::Map(TiXmlHandle rootHandle) {
    mapDescription = "Untitled";
    startx = 0;
    starty = 0;
    finishx = 0;
    finishy = 0;
    cellsize = DEFAULT_CELLSIZE;
    height = 0;
    width = 0;
    grid = NULL;

    GetMapFromXML(rootHandle);
}

Map::~Map () {
    for (int i = 0; i < height; i++) {
        delete [] grid[i];
    }
    delete [] grid;
}

void Map::GetMapFromXML(TiXmlHandle rootHandle) {
    Utils::parseValueFromXmlNode(rootHandle, TAG_DESC, mapDescription);

    TiXmlHandle mapHandle = rootHandle.FirstChild( TAG_MAP_CONTAINER );
    if(!mapHandle.ToElement()) throw MissingTagError( TAG_MAP_CONTAINER );

    Utils::parseValueFromXmlNode(mapHandle, TAG_MAP_WIDTH, width, true);
    Utils::parseValueFromXmlNode(mapHandle, TAG_MAP_HEIGHT, height, true);
    Utils::parseValueFromXmlNode(mapHandle, TAG_CELLSIZE, cellsize);
    Utils::parseValueFromXmlNode(mapHandle, TAG_START_X, startx);
    Utils::parseValueFromXmlNode(mapHandle, TAG_START_Y, starty);
    Utils::parseValueFromXmlNode(mapHandle, TAG_FINISH_X, finishx);
    Utils::parseValueFromXmlNode(mapHandle, TAG_FINISH_Y, finishy);

    TiXmlHandle gridHandle = mapHandle.FirstChild( TAG_GRID );
    if(!gridHandle.ToElement()) throw MissingTagError( TAG_GRID );

    grid = new int * [height];
    for(int i = 0; i < height; i++){
        grid[i] = new int [width];
    }

    TiXmlElement* rowAsXmlElement;
    for(int i = 0; i < height; i++) {
        rowAsXmlElement = gridHandle.ChildElement( TAG_GRID_ROW, i).ToElement();
        if(!rowAsXmlElement) MissingTagError( TAG_GRID_ROW );
        /*
         * throw with line numbers, to be implemented
         */
        std::stringstream rowStream(rowAsXmlElement->GetText());
        for(int j = 0; j < width; j++){
            rowStream >> grid[i][j];
            rowStream.ignore(1, INPUT_GRID_SEPARATOR );
        }
    }
}

TiXmlElement* Map::DumpToXmlElement() {
    TiXmlElement* mapContainer = new TiXmlElement( TAG_MAP_CONTAINER );

    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(mapDescription, TAG_DESC ));
    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(width, TAG_MAP_WIDTH));
    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(height, TAG_MAP_HEIGHT));
    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(cellsize, TAG_CELLSIZE));
    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(startx, TAG_START_X));
    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(starty, TAG_START_Y));
    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(finishx, TAG_FINISH_X));
    mapContainer->LinkEndChild(Utils::dumpValueToXmlNode(finishy, TAG_FINISH_Y));

    TiXmlElement* gridEl = new TiXmlElement( TAG_GRID );
    for (int i = 0; i < height; i++) {
        std::stringstream rowStream;

        for(int j = 0; j < width; j++) {
            rowStream << grid[i][j] << OUTPUT_MAP_SEPARATOR;
        }

        TiXmlElement* rowEl = Utils::dumpValueToXmlNode( rowStream.str(), TAG_GRID_ROW );
        rowEl->SetDoubleAttribute( OUTPUT_LINE_NUMBER_ATTR , i + 1);
        gridEl->LinkEndChild(rowEl);
    }
    mapContainer->LinkEndChild(gridEl);

    return mapContainer;
}

int Map::GetMapArea() {
    return height * width;
}

int Map::GetHeight() {
    return height;
}

int Map::GetWidth() {
    return width;
}

int Map::At(int i, int j) {
    if (i < 0 || i >= height || j < 0 || j >= width)
        return ELEMENT_OUT_OF_GRID;
    return grid[i][j];
}

int Map::At(Utils::Coords coords) {
    if (coords.x < 0 || coords.x >= height || coords.y < 0 || coords.y >= width)
        return ELEMENT_OUT_OF_GRID;
    return grid[coords.x][coords.y];
}

std::ostream& operator<< (std::ostream &os, const Map& map) {
    os << "Map \"" << map.mapDescription << "\":" << std::endl;
    os << "size " << map.height << "x" << map.width << ", cellsize " << map.cellsize << std::endl;
    os << "looking for route from (" << map.startx << ", " << map.starty << ") to (" << map.finishx << ", " <<
                                                                                        map.finishy << ")" << std::endl;
    return os;
}
