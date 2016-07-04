#ifndef XMLOBJECT_H
#define XMLOBJECT_H

#include "gl_settings.h"
#include "logger.h"
#include "map.h"
#include "pathfindingtask.h"
#include "options.h"
#include "mapanalyzer.h"

class XMLObject
{
public:
    XMLObject(const char *);
    ~XMLObject();

    void SetLogPath(const char *);
    void LoadFromFile(const char *);
    void AnalyzeMap();
    void FindPath();

    friend std::ostream& operator<< (std::ostream &, const XMLObject &);
    void DumpToFile();

    void LogMessage(std::string);

    LoggerInterface logger;

private:
    Map *map;
    PathfindingTask *algorithm;
    Options *options;
    MapAnalyzer *analyser;
    std::string fPath;
};

#endif // XMLOBJECT_H
