#ifndef OPTIONS_H
#define OPTIONS_H

#include "gl_settings.h"

class Options {
public:
    Options(TiXmlHandle);
    ~Options();

    TiXmlElement* DumpToXmlElement();
private:
    int logLevel;
    std::string logPath;
    std::string logFileName;

    bool GetDataFromXml(TiXmlHandle);
};

#endif // OPTIONS_H
