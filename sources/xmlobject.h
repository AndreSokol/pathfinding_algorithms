#ifndef XMLOBJECT_H
#define XMLOBJECT_H

#include "gl_settings.h"

class XMLObject
{
public:
    XMLObject(const char *);
    ~XMLObject();

    void SetLogPath(const char *);
    void LoadFromFile(const char *);
    void AnalyzeMap();

    friend std::ostream& operator<< (std::ostream &, const XMLObject &);
    void DumpToFile();

    void LogMessage(std::string);

    Logger logger;
private:
    Map *map;
    Algorithm *algorithm;
    Options *options;
    std::string fPath;
    MapAnalyzer *analyser;
};

#endif // XMLOBJECT_H
