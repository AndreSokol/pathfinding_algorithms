#ifndef LOGGER_H
#define LOGGER_H

#include "gl_settings.h"

class Logger
{
public:
    Logger();
    ~Logger();

    Logger& operator << (std::ostream &(*pManip)(std::ostream &));
    template <typename Type> Logger& operator << (Type);

    void SetLogPath(const char *);
    std::string LogPath();
private:
    bool writeToConsole;
    std::string logPath;
    bool writeToFile;
    std::ofstream fileOutput;
};



#endif // LOGGER_H
