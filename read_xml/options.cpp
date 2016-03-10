#include "options.h"
#include "gl_settings.h"


Options::Options() {
    this->logLevel = 1;
    this->logPath = "";
    this->logFileName = "";
}

Options::~Options() {
    // to be implemented
}

bool Options::GetDataFromXml(TiXmlHandle optionsHandle) {
    if(!optionsHandle.ToElement()) return false;

    TiXmlElement * logLevel = optionsHandle.FirstChild( TAG_OPTIONS_LOG_LEVEL ).ToElement();
    if(logLevel) std::istringstream(logLevel->GetText()) >> this->logLevel;
    else         Utils::ReportTagMissing( TAG_OPTIONS_LOG_FILENAME , this->logLevel);


    // TO BE IMPLEMENTED

    //TiXmlElement * logPath = optionsHandle.FirstChild( TAG_OPTIONS_LOG_PATH ).ToElement();
    //if(logPath) this->logPath = logPath->GetText();

    //TiXmlElement * logFileName = optionsHandle.FirstChild( TAG_OPTIONS_LOG_FILENAME ).ToElement();
    //if(logFileName) this->logFileName = logFileName->GetText();

    return true;
}
