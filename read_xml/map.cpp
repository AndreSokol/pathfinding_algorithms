#include "map.h"
#include "gl_settings.h"

/*
 * class Algorithm
 */

Algorithm::Algorithm (){
    this->searchType = "astar";
    this->metricType = "euclid";
    this->hWeight = 1.0;
    this->breakingTies = "gmax";
    this->lineCost = 1.0;
    this->diagonalCost = 1.414;
    this->allowDiagonal = false;
    this->allowSqueeze = false;
}

bool Algorithm::GetDataFromXml(TiXmlHandle algoHandle) {
    if(!algoHandle.ToElement()) return false;

    TiXmlElement * algoType = algoHandle.FirstChild( TAG_ALGO_TYPE ).ToElement();
    if(algoType) this->searchType = algoType->GetText();
    else         ReportTagMissing( TAG_ALGO_TYPE , this->searchType);

    TiXmlElement * algoMetric = algoHandle.FirstChild( TAG_ALGO_METRIC ).ToElement();
    if(algoMetric) this->metricType = algoMetric->GetText();
    else           ReportTagMissing( TAG_ALGO_METRIC , this->metricType);

    TiXmlElement * algoHweight = algoHandle.FirstChild( TAG_ALGO_HWEIGHT ).ToElement();
    if(algoHweight) std::istringstream(algoHweight->GetText()) >> this->hWeight;
    else            ReportTagMissing( TAG_ALGO_HWEIGHT , this->hWeight);

    TiXmlElement * algoTieBreak = algoHandle.FirstChild( TAG_ALGO_TIE_BRAKE ).ToElement();
    if(algoTieBreak) this->breakingTies = algoTieBreak->GetText();
    else             ReportTagMissing( TAG_ALGO_TIE_BRAKE , this->breakingTies);

    TiXmlElement * algoLineCost = algoHandle.FirstChild( TAG_ALGO_LINE_COST ).ToElement();
    if(algoLineCost) std::istringstream(algoLineCost->GetText()) >> this->lineCost;
    else             ReportTagMissing( TAG_ALGO_LINE_COST , this->lineCost);

    TiXmlElement * algoDiagCost = algoHandle.FirstChild( TAG_ALGO_DIAG_COST ).ToElement();
    if(algoDiagCost) std::istringstream(algoDiagCost->GetText()) >> this->diagonalCost;
    else             ReportTagMissing( TAG_ALGO_DIAG_COST , this->diagonalCost);

    TiXmlElement * algoAllowDiag = algoHandle.FirstChild( TAG_ALGO_ALLOW_DIAG ).ToElement();
    if(algoAllowDiag) std::istringstream(algoAllowDiag->GetText()) >> this->allowDiagonal;
    else              ReportTagMissing( TAG_ALGO_ALLOW_DIAG , this->allowDiagonal);

    TiXmlElement * algoAllowSqueeze = algoHandle.FirstChild( TAG_ALGO_ALLOW_SQUEEZE ).ToElement();
    if(algoAllowSqueeze) std::istringstream(algoAllowSqueeze->GetText()) >> this->allowSqueeze;
    else                 ReportTagMissing( TAG_ALGO_ALLOW_SQUEEZE , this->allowSqueeze);

    return true;
}

Algorithm::~Algorithm() {
    // to be implemented
}

std::ostream& operator<< (std::ostream &os, const Algorithm& algo) {
    os << algo.searchType << " in " << algo.metricType << " metric" << std::endl;
    os << algo.diagonalCost << std::endl;
    return os;
}

TiXmlElement* Algorithm::DumpToXmlElement() {
    TiXmlElement* root = new TiXmlElement( TAG_ALGO_CONTAINER );

    TiXmlElement* searchTypeEl = new TiXmlElement( TAG_ALGO_TYPE );
    searchTypeEl->LinkEndChild(new TiXmlText(this->searchType));
    root->LinkEndChild(searchTypeEl);

    TiXmlElement* metricTypeEl = new TiXmlElement( TAG_ALGO_METRIC );
    metricTypeEl->LinkEndChild(new TiXmlText(this->metricType));
    root->LinkEndChild(metricTypeEl);

    TiXmlElement* hweightEl = new TiXmlElement( TAG_ALGO_HWEIGHT );
    hweightEl->LinkEndChild(new TiXmlText( toString(this->hWeight) ));
    root->LinkEndChild(hweightEl);

    TiXmlElement* breakingTiesEl = new TiXmlElement( TAG_ALGO_TIE_BRAKE );
    breakingTiesEl->LinkEndChild(new TiXmlText(this->breakingTies));
    root->LinkEndChild(breakingTiesEl);

    TiXmlElement* lineCostEl = new TiXmlElement( TAG_ALGO_LINE_COST );
    lineCostEl->LinkEndChild(new TiXmlText( toString(this->lineCost) ));
    root->LinkEndChild(lineCostEl);

    TiXmlElement* diagonalCostEl = new TiXmlElement( TAG_ALGO_DIAG_COST );
    diagonalCostEl->LinkEndChild(new TiXmlText( toString(this->diagonalCost) ));
    root->LinkEndChild(diagonalCostEl);

    TiXmlElement* allowDiagonalEl = new TiXmlElement( TAG_ALGO_ALLOW_DIAG );
    allowDiagonalEl->LinkEndChild(new TiXmlText( toString(this->allowDiagonal) ));
    root->LinkEndChild(allowDiagonalEl);

    TiXmlElement* allowSqueezeEl = new TiXmlElement( TAG_ALGO_ALLOW_SQUEEZE );
    allowSqueezeEl->LinkEndChild(new TiXmlText( toString(this->allowSqueeze) ));
    root->LinkEndChild(allowSqueezeEl);

    return root;
}

/*
 * class Options
 */

Options::Options() {
    this->logLevel = 1;
    this->logPath = "";
    this->logFileName = "";
}

Options::~Options() {
    // to be implemented
}

bool Options::GetDataFromXml(TiXmlHandle optionsHandle) {
    if(!optionsHandle.ToElement()) return false;

    TiXmlElement * logLevel = optionsHandle.FirstChild( TAG_OPTIONS_LOG_LEVEL ).ToElement();
    if(logLevel) std::istringstream(logLevel->GetText()) >> this->logLevel;
    else         ReportTagMissing( TAG_OPTIONS_LOG_FILENAME , this->logLevel);


    // TO BE IMPLEMENTED

    //TiXmlElement * logPath = optionsHandle.FirstChild( TAG_OPTIONS_LOG_PATH ).ToElement();
    //if(logPath) this->logPath = logPath->GetText();

    //TiXmlElement * logFileName = optionsHandle.FirstChild( TAG_OPTIONS_LOG_FILENAME ).ToElement();
    //if(logFileName) this->logFileName = logFileName->GetText();

    return true;
}

/*
 * class Map
 */

Map::Map() {
    this->map_description = "Untitled";
//Algorithm and Options are independent entities. NOT part of map entity!
    this->algorithm = new Algorithm();
    this->options = new Options();
    this->startx = 0;
    this->starty = 0;
    this->finishx = 0;
    this->finishy = 0;
//better - set default cellsize via constant devin in gl_settings
    this->cellsize = 1;
    this->height = 0;
    this->width = 0;
    this->grid = NULL;
}

Map::~Map () {
    for (int i = 0; i < this->height; i++) {
        delete [] grid[i];
    }
    delete [] grid;

    delete this->algorithm;
    delete this->options;
}

bool Map::GetMapFromXML(const char * fPath) {
    TiXmlDocument doc;
    doc.LoadFile(fPath);
    TiXmlHandle docHandle( &doc );

    TiXmlHandle rootHandle = docHandle.FirstChild( TAG_ROOT );
    if(!rootHandle.ToElement()) return false;

    TiXmlElement* mapDesc = rootHandle.FirstChild( TAG_DESC ).ToElement();
    if(!mapDesc) ReportTagMissing( TAG_DESC , this->map_description);
    else         this->map_description = mapDesc->GetText();

    TiXmlHandle mapHandle = rootHandle.FirstChild( TAG_MAP_CONTAINER );
    if(!mapHandle.ToElement()) return false;

    TiXmlElement* map_width = mapHandle.FirstChildElement( TAG_MAP_WIDTH ).ToElement();
    if(!map_width) return false;//Will user know what happened here? Why program stopped working? Any message to him?
    std::istringstream(map_width->GetText()) >> this->width;

    TiXmlElement* map_height = mapHandle.FirstChildElement( TAG_MAP_HEIGHT ).ToElement();
    if(!map_height) return false;
    std::istringstream(map_height->GetText()) >> this->height;

    TiXmlElement* map_cellsize = mapHandle.FirstChildElement( TAG_CELLSIZE ).ToElement();
    if(!map_cellsize) ReportTagMissing(TAG_CELLSIZE, this->cellsize);
    else              std::istringstream(map_cellsize->GetText()) >> this->cellsize;

    TiXmlElement* map_startx = mapHandle.FirstChildElement( TAG_START_X ).ToElement();
    if(!map_startx) ReportTagMissing(TAG_START_X, this->startx);
    else            std::istringstream(map_startx->GetText()) >> this->startx;

    TiXmlElement* map_starty = mapHandle.FirstChildElement( TAG_START_Y ).ToElement();
    if(!map_starty) ReportTagMissing(TAG_START_Y, this->starty);
    else            std::istringstream(map_starty->GetText()) >> this->starty;

    TiXmlElement* map_finishx = mapHandle.FirstChildElement( TAG_FINISH_X ).ToElement();
    if(!map_finishx) ReportTagMissing(TAG_FINISH_X, this->finishx);
    else             std::istringstream(map_finishx->GetText()) >> this->finishx;

    TiXmlElement* map_finishy = mapHandle.FirstChildElement( TAG_FINISH_Y ).ToElement();
    if(!map_finishy) ReportTagMissing(TAG_FINISH_Y, this->finishy);
    else             std::istringstream(map_finishy->GetText()) >> this->finishy;

    TiXmlHandle gridHandle = mapHandle.FirstChild( TAG_GRID );
    if(!gridHandle.ToElement()) return false;

    this->grid = new int * [this->height];
    for(int i = 0; i < this->height; i++){
        this->grid[i] = new int [this->width];
    }

    TiXmlElement* rowAsXmlElement;
    for(int i = 0; i < this->height; i++) {
        rowAsXmlElement = gridHandle.ChildElement( TAG_GRID_ROW, i).ToElement();
        if(!rowAsXmlElement) return false;

        std::stringstream rowStream(rowAsXmlElement->GetText());
        for(int j = 0; j < this->width; j++){
//Will it work with other separators except " "?
            rowStream >> this->grid[i][j];
        }
    }

    TiXmlHandle algoHandle = rootHandle.FirstChild( TAG_ALGO_CONTAINER );
    this->algorithm->GetDataFromXml(algoHandle);

    TiXmlHandle optionsHandle = rootHandle.FirstChild( TAG_OPTIONS_CONTAINER );
    this->options->GetDataFromXml(optionsHandle);

    return true;
}

void Map::DumpToXML(const char * fPath) {
    TiXmlDocument doc;
    TiXmlElement* root = new TiXmlElement( TAG_ROOT );
    TiXmlElement* mapContainer = new TiXmlElement( TAG_MAP_CONTAINER );

    TiXmlElement* mapDesc = new TiXmlElement( TAG_DESC );
    mapDesc->LinkEndChild(new TiXmlText(this->map_description));
    mapContainer->LinkEndChild(mapDesc);

    TiXmlElement* widthEl = new TiXmlElement( TAG_MAP_WIDTH );
    widthEl->LinkEndChild(new TiXmlText( toString(this->width) ));
    mapContainer->LinkEndChild(widthEl);

    TiXmlElement* heightEl = new TiXmlElement( TAG_MAP_HEIGHT );
    heightEl->LinkEndChild(new TiXmlText( toString(this->height) ));
    mapContainer->LinkEndChild(heightEl);

    TiXmlElement* cellsizeEl = new TiXmlElement( TAG_CELLSIZE );
    cellsizeEl->LinkEndChild(new TiXmlText( toString(this->cellsize) ));
    mapContainer->LinkEndChild(cellsizeEl);

    TiXmlElement* startxEl = new TiXmlElement( TAG_START_X );
    startxEl->LinkEndChild(new TiXmlText( toString(this->startx) ));
    mapContainer->LinkEndChild(startxEl);

    TiXmlElement* startyEl = new TiXmlElement( TAG_START_Y );
    startyEl->LinkEndChild(new TiXmlText( toString(this->starty) ));
    mapContainer->LinkEndChild(startyEl);

    TiXmlElement* finishxEl = new TiXmlElement( TAG_FINISH_X );
    finishxEl->LinkEndChild(new TiXmlText( toString(this->finishx) ));
    mapContainer->LinkEndChild(finishxEl);

    TiXmlElement* finishyEl = new TiXmlElement( TAG_FINISH_Y );
    finishyEl->LinkEndChild(new TiXmlText( toString(this->finishy) ));
    mapContainer->LinkEndChild(finishyEl);

    TiXmlElement* gridEl = new TiXmlElement( TAG_GRID );
    for (int i = 0; i < this->height; i++) {
        TiXmlElement* rowEl = new TiXmlElement( TAG_GRID_ROW );
//"number" - bad. should be constant.
        rowEl->SetDoubleAttribute("number", i + 1);

        std::stringstream rowStream;
        for(int j = 0; j < this->width; j++) {
//well " " also better be constant. May be we want another separator (like "_" or "-") the other day?
            rowStream << this->grid[i][j] << " ";
        }
        rowEl->LinkEndChild(new TiXmlText(rowStream.str()));
        gridEl->LinkEndChild(rowEl);
    }
    mapContainer->LinkEndChild(gridEl);

    root->LinkEndChild(mapContainer);

    TiXmlElement * algoContainer = this->algorithm->DumpToXmlElement();
    root->LinkEndChild(algoContainer);

//"output", "density" - constants!
    TiXmlElement * outputContainer = new TiXmlElement("output");
    TiXmlElement * densityEl = new TiXmlElement("density");
    densityEl->LinkEndChild(new TiXmlText( toString(this->CalculateDensity()) ));
    outputContainer->LinkEndChild(densityEl);
    root->LinkEndChild(outputContainer);

    doc.LinkEndChild(root);
    doc.SaveFile(fPath);
}

double Map::CalculateDensity() {
    double answer = 0;
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            if (this->grid[i][j] != 0) answer++;
        }
    }

    return answer / this->width / this->height;
}

std::ostream& operator<< (std::ostream &os, const Map& map) {
    os << "Map \"" << map.map_description << "\":" << std::endl;
    os << "size " << map.height << "x" << map.width << ", cellsize " << map.cellsize << std::endl;
    os << "looking for route from (" << map.startx << ", " << map.starty << ") to (" << map.finishx << ", " <<
                                                                                        map.finishy << ")" << std::endl;
    os << "with following algorithm:" << std::endl;
    os << *(map.algorithm);

    return os;
}

/*
 * Utils
 */

template <typename Type>
std::string toString(const Type& element) {
    std::stringstream sstream;
    sstream << element;
    return sstream.str();
}

//First business logic shall be agreed. Some tags can be missed (with default values set). Some - can not! So
// there are two types of tag-handling: Error (program should terminate) and Warning - program should warn and continue.
template <typename Type>
void ReportTagMissing(const std::string & tag, const Type & default_value) {
    std::cerr << "[WARNING] Tag '" << tag << "' is missing; default value " << default_value << " set." << std::endl;
}
