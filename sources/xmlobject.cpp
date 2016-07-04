#include "xmlobject.h"
#include "logger.h"
#include "map.h"
#include "pathfindingtask.h"
#include "mapanalyzer.h"
#include "options.h"
#include "errors.cpp"

XMLObject::XMLObject(const char * inputFileName)
{
    map = NULL;
    algorithm = NULL;
    options = NULL;
    fPath = "";
    analyser = NULL;
    logger.SetLogPath(inputFileName);
}

XMLObject::~XMLObject()
{
    delete map;
    delete algorithm;
    delete options;
    delete analyser;
}

void XMLObject::SetLogPath(const char * logPath) {
    logger.SetLogPath(logPath);
}

void XMLObject::LoadFromFile(const char * fPath) {
    this->fPath = fPath;

    TiXmlDocument doc;
    doc.LoadFile(fPath);

    logger << "[INFO] Reading file from '" << fPath << "'" << "\n";

    if( doc.Error() ) throw ParserError(doc.ErrorDesc(), fPath);
    TiXmlHandle docHandle( &doc );


    TiXmlHandle rootHandle = docHandle.FirstChild( TAG_ROOT );
    if(!rootHandle.ToElement()) throw MissingTagError( TAG_ROOT );

    map = new Map(rootHandle);
    options = new Options(rootHandle);
    algorithm = new PathfindingTask(rootHandle);

    logger << "[INFO] Reading from file done!" << std::endl;
}

void XMLObject::AnalyzeMap() {
    logger << "[INFO] Analysing map..." << std::endl;
    analyser = new MapAnalyzer(map);
    logger << "[INFO] Analysis done!" << std::endl;
}

void XMLObject::DumpToFile() {
    std::string fPath = "output.xml";

    logger << "[INFO] Dumping results to XML..." << std::endl;

    TiXmlDocument doc;
    TiXmlElement* rootElement = new TiXmlElement( TAG_ROOT );

    rootElement->LinkEndChild( map->DumpToXmlElement() );
    rootElement->LinkEndChild( algorithm->DumpToXmlElement() );
    rootElement->LinkEndChild( options->DumpToXmlElement() );

    if (analyser != NULL) rootElement->LinkEndChild( analyser->DumpToXmlElement( options->getLogLevel() ) );
    else logger << "[WARNING] Map was not analyzed! No results attached to output file." << std::endl;

    doc.LinkEndChild(rootElement);
    doc.SaveFile( fPath );

    logger << "[INFO] Dumping results to XML done, look at " << fPath << std::endl;
}

void XMLObject::LogMessage(std::string msg)
{
    std::cout << msg << std::endl;
}


std::ostream& operator<< (std::ostream & os, const XMLObject & a) {
    if(a.analyser != NULL) os << *(a.analyser);
    else                   os << "Map has not yet been analyzed" << std::endl;

    return os;
}

void XMLObject::FindPath() {
    algorithm->FindPath(map);
}
