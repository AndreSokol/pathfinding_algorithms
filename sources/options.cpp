#include "options.h"
#include "gl_settings.h"
#include "logger.h"
#include "utils.h"
#include "errors.cpp"

Options::Options(TiXmlHandle rootHandle, Logger* logger) {
    logLevel = 1;
    logPath = "";
    logFileName = "";
    this->logger = logger;

    GetDataFromXml(rootHandle);
}

Options::~Options() {
    // to be implemented
}

int Options::getLogLevel() {
    return logLevel;
}

TiXmlElement* Options::DumpToXmlElement()
{
    TiXmlElement* root = new TiXmlElement( TAG_OPTIONS_CONTAINER );

    *logger << "[INFO] Dumping options to XML..." << std::endl;
    root->LinkEndChild(Utils::dumpValueToXmlNode(logLevel, TAG_OPTIONS_LOG_LEVEL ));
    *logger << "[INFO] Dumping options to XML done!" << std::endl;

    return root;
}

bool Options::GetDataFromXml(TiXmlHandle rootHandle) {
    *logger << "[INFO] Reading options from XML..." << std::endl;
    TiXmlHandle optionsHandle = rootHandle.FirstChild( TAG_OPTIONS_CONTAINER );
    if(!optionsHandle.ToElement()) throw MissingTagError( TAG_OPTIONS_CONTAINER );

    TiXmlElement * logLevelEl = optionsHandle.FirstChild( TAG_OPTIONS_LOG_LEVEL ).ToElement();
    if(logLevelEl) std::istringstream( logLevelEl->GetText() ) >> logLevel;
    else           Utils::ReportTagMissing( TAG_OPTIONS_LOG_FILENAME , logLevel);

    *logger << "[INFO] Reading options done!" << std::endl;
    // TO BE IMPLEMENTED

    //TiXmlElement * logPath = optionsHandle.FirstChild( TAG_OPTIONS_LOG_PATH ).ToElement();
    //if(logPath) this->logPath = logPath->GetText();
    //else        Utils::ReportTagMissing( TAG_OPTIONS_LOG_FILENAME , this->logLevel);

    //TiXmlElement * logFileName = optionsHandle.FirstChild( TAG_OPTIONS_LOG_FILENAME ).ToElement();
    //if(logFileName) this->logFileName = logFileName->GetText();

    return true;
}
