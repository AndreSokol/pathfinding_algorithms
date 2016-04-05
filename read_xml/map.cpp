#include "map.h"
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
    TiXmlElement* mapDesc = rootHandle.FirstChild( TAG_DESC ).ToElement();
    if(!mapDesc) Utils::ReportTagMissing( TAG_DESC , this->mapDescription);
    else         mapDescription = mapDesc->GetText();

    TiXmlHandle mapHandle = rootHandle.FirstChild( TAG_MAP_CONTAINER );
    if(!mapHandle.ToElement()) throw MissingTagError( TAG_MAP_CONTAINER );

    TiXmlElement* map_width = mapHandle.FirstChildElement( TAG_MAP_WIDTH ).ToElement();
    if(!map_width) throw MissingTagError( TAG_MAP_WIDTH );
    std::istringstream(map_width->GetText()) >> width;

    TiXmlElement* map_height = mapHandle.FirstChildElement( TAG_MAP_HEIGHT ).ToElement();
    if(!map_height) throw MissingTagError( TAG_MAP_HEIGHT );
    std::istringstream(map_height->GetText()) >> height;

    TiXmlElement* map_cellsize = mapHandle.FirstChildElement( TAG_CELLSIZE ).ToElement();
    if(!map_cellsize) Utils::ReportTagMissing(TAG_CELLSIZE, cellsize);
    else              std::istringstream(map_cellsize->GetText()) >> cellsize;

    TiXmlElement* map_startx = mapHandle.FirstChildElement( TAG_START_X ).ToElement();
    if(!map_startx) Utils::ReportTagMissing(TAG_START_X, startx);
    else            std::istringstream(map_startx->GetText()) >> startx;

    TiXmlElement* map_starty = mapHandle.FirstChildElement( TAG_START_Y ).ToElement();
    if(!map_starty) Utils::ReportTagMissing(TAG_START_Y, starty);
    else            std::istringstream(map_starty->GetText()) >> starty;

    TiXmlElement* map_finishx = mapHandle.FirstChildElement( TAG_FINISH_X ).ToElement();
    if(!map_finishx) Utils::ReportTagMissing(TAG_FINISH_X, finishx);
    else             std::istringstream(map_finishx->GetText()) >> finishx;

    TiXmlElement* map_finishy = mapHandle.FirstChildElement( TAG_FINISH_Y ).ToElement();
    if(!map_finishy) Utils::ReportTagMissing(TAG_FINISH_Y, finishy);
    else             std::istringstream(map_finishy->GetText()) >> finishy;

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

    TiXmlElement* mapDesc = new TiXmlElement( TAG_DESC );
    mapDesc->LinkEndChild(new TiXmlText(mapDescription));
    mapContainer->LinkEndChild(mapDesc);

    TiXmlElement* widthEl = new TiXmlElement( TAG_MAP_WIDTH );
    widthEl->LinkEndChild(new TiXmlText( Utils::toString(width) ));
    mapContainer->LinkEndChild(widthEl);

    TiXmlElement* heightEl = new TiXmlElement( TAG_MAP_HEIGHT );
    heightEl->LinkEndChild(new TiXmlText( Utils::toString(height) ));
    mapContainer->LinkEndChild(heightEl);

    TiXmlElement* cellsizeEl = new TiXmlElement( TAG_CELLSIZE );
    cellsizeEl->LinkEndChild(new TiXmlText( Utils::toString(cellsize) ));
    mapContainer->LinkEndChild(cellsizeEl);

    TiXmlElement* startxEl = new TiXmlElement( TAG_START_X );
    startxEl->LinkEndChild(new TiXmlText( Utils::toString(startx) ));
    mapContainer->LinkEndChild(startxEl);

    TiXmlElement* startyEl = new TiXmlElement( TAG_START_Y );
    startyEl->LinkEndChild(new TiXmlText( Utils::toString(starty) ));
    mapContainer->LinkEndChild(startyEl);

    TiXmlElement* finishxEl = new TiXmlElement( TAG_FINISH_X );
    finishxEl->LinkEndChild(new TiXmlText( Utils::toString(finishx) ));
    mapContainer->LinkEndChild(finishxEl);

    TiXmlElement* finishyEl = new TiXmlElement( TAG_FINISH_Y );
    finishyEl->LinkEndChild(new TiXmlText( Utils::toString(finishy) ));
    mapContainer->LinkEndChild(finishyEl);

    TiXmlElement* gridEl = new TiXmlElement( TAG_GRID );
    for (int i = 0; i < height; i++) {
        TiXmlElement* rowEl = new TiXmlElement( TAG_GRID_ROW );
        rowEl->SetDoubleAttribute( OUTPUT_LINE_NUMBER_ATTR , i + 1);

        std::stringstream rowStream;
        for(int j = 0; j < width; j++) {
            rowStream << grid[i][j] << OUTPUT_MAP_SEPARATOR;
        }
        rowEl->LinkEndChild(new TiXmlText(rowStream.str()));
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
