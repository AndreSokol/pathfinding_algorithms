#include "logger.h"

Logger::Logger()
{
    logPath = "";
    writeToFile = false;
    writeToConsole = true;
}

Logger::~Logger() {
    if(writeToFile) fileOutput.close();
}

void Logger::SetLogPath(const char * logPath) {
    std::string logPathPrepare = std::string(logPath);
    logPathPrepare = logPathPrepare.substr(0, logPathPrepare.length() - 4) + ".txt";
    this->logPath = logPathPrepare.c_str();
    fileOutput.open(this->logPath);
    writeToFile = true;
}

Logger& Logger::operator << (std::ostream&(*pManip)(std::ostream&)) {
    if(writeToConsole) std::cout << (*pManip);
    if(writeToFile) fileOutput << (*pManip);
    return (*this);
}

std::string Logger::LogPath() {
    return std::string(logPath);
}
