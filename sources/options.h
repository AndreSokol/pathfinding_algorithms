#ifndef OPTIONS_H
#define OPTIONS_H

#include "gl_settings.h"
#include "logger.h"

class Options {
public:
    Options(TiXmlHandle);
    ~Options();

    TiXmlElement* DumpToXmlElement();
    int getLogLevel();
private:
    int logLevel;
    std::string logPath;
    std::string logFileName;
    LoggerInterface logger;

    bool GetDataFromXml(TiXmlHandle);
};

#endif // OPTIONS_H
