#include "logger.h"

Logger::Logger()
{
    logPath = "logs.txt";
    writeToFile = false;
    writeToConsole = true;
}

Logger::~Logger() {
    if(writeToFile) fileOutput.close();
}

void Logger::SetLogPath(const char * logPath) {
    this->logPath = logPath;
    fileOutput.open(logPath);
    writeToFile = true;
}

Logger& Logger::operator << (std::ostream&(*pManip)(std::ostream&)) {
    if(writeToConsole) std::cout << (*pManip);
    if(writeToFile) fileOutput << (*pManip);
    return (*this);
}

template <typename Type>
Logger& Logger::operator << (Type msg) {
    if(writeToConsole) std::cout << msg;
    if(writeToFile) fileOutput << msg;
    return (*this);
}
