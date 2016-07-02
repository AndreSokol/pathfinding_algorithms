#ifndef LOGGER_H
#define LOGGER_H

#include "gl_settings.h"

class Logger
{
public:
    Logger();
    ~Logger();

    Logger& operator<< (std::ostream &(*pManip)(std::ostream &));

    // Not sure but it seems we need to implement template functions in header (otherwise aren't compiling)
    template <typename Type>
    Logger& operator<< (Type msg) {
        if(writeToConsole) std::cout << msg;
        if(writeToFile)    fileOutput << msg;
        return (*this);
    }


    void SetLogPath(const char *);
    std::string LogPath();
private:
    bool writeToConsole;
    std::string logPath;
    bool writeToFile;
    std::ofstream fileOutput;
};



#endif // LOGGER_H
