#ifndef OPTIONS_H
#define OPTIONS_H

#include "gl_settings.h"

class Options {
public:
    Options(TiXmlHandle, Logger*);
    ~Options();

    TiXmlElement* DumpToXmlElement();
    int getLogLevel();
private:
    int logLevel;
    std::string logPath;
    std::string logFileName;
    Logger *logger;

    bool GetDataFromXml(TiXmlHandle);
};

#endif // OPTIONS_H
