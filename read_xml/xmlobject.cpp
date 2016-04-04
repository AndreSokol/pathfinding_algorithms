#include "xmlobject.h"

XMLObject::XMLObject()
{
    map = NULL;
    algorithm = NULL;
    options = NULL;
    fPath = "";
    analyser = NULL;
}

XMLObject::~XMLObject()
{
    delete map;
    delete algorithm;
    delete options;
    delete analyser;
}

void XMLObject::LoadFromFile(const char * fPath) {
    this->fPath = fPath;

    TiXmlDocument doc;
    doc.LoadFile(fPath);

    if( doc.Error() ) throw ParserError(doc.ErrorDesc(), fPath);
    TiXmlHandle docHandle( &doc );


    TiXmlHandle rootHandle = docHandle.FirstChild( TAG_ROOT );
    if(!rootHandle.ToElement()) throw MissingTagError( TAG_ROOT );

    map = new Map(rootHandle);
    options = new Options(rootHandle);
    algorithm = new Algorithm(rootHandle);
}

void XMLObject::AnalyzeMap() {
    analyser = new MapAnalyzer(map);
}

void XMLObject::DumpToFile() {
    std::string fPath = "output.xml";

    TiXmlDocument doc;
    TiXmlElement* rootElement = new TiXmlElement( TAG_ROOT );

    rootElement->LinkEndChild(map->DumpToXmlElement());
    rootElement->LinkEndChild(algorithm->DumpToXmlElement());
    rootElement->LinkEndChild(options->DumpToXmlElement());

    if (analyser != NULL) // RAISE WARNING, TO BE IMPLEMENTED
        rootElement->LinkEndChild(analyser->DumpToXmlElement());

    doc.LinkEndChild(rootElement);
    doc.SaveFile(fPath);
}


std::ostream& operator<< (std::ostream & os, const XMLObject & a) {
    os << *(a.analyser);
    return os;
}
