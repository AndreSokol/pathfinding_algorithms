#ifndef LOGGER_H
#define LOGGER_H

#include "gl_settings.h"

class Logger
{
public:
    Logger();
    Logger(const Logger &other);
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

class LoggerInterface {
public:
    template <typename Type> LoggerInterface& operator<< (Type msg) {
        logger << msg;
        return (*this);
    }

    LoggerInterface& operator<<(std::ostream &(*pManip)(std::ostream &)) {
        logger << pManip;
        return (*this);
    }

    void SetLogPath(const char * logPath) {
        logger.SetLogPath(logPath);
    }

    std::string LogPath() {
        return logger.LogPath();
    }
private:
    static Logger logger;
};

#endif // LOGGER_H
