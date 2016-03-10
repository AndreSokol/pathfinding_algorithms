#ifndef OPTIONS_H
#define OPTIONS_H

#include "gl_settings.h"

class Options {
public:
    Options();
    ~Options();

    bool GetDataFromXml(TiXmlHandle);
private:
    int logLevel;
    std::string logPath;
    std::string logFileName;
};

#endif // OPTIONS_H
