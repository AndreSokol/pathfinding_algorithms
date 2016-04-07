#include "options.h"
#include "gl_settings.h"


Options::Options(TiXmlHandle rootHandle) {
    logLevel = 1;
    logPath = "";
    logFileName = "";

    GetDataFromXml(rootHandle);
}

Options::~Options() {
    // to be implemented
}

TiXmlElement* Options::DumpToXmlElement()
{
    TiXmlElement* root = new TiXmlElement( TAG_OPTIONS_CONTAINER );

    TiXmlElement* logLevelEl = new TiXmlElement( TAG_OPTIONS_LOG_LEVEL );
    logLevelEl->LinkEndChild(new TiXmlText(Utils::toString(logLevel)));
    root->LinkEndChild(logLevelEl);

    return root;
}

bool Options::GetDataFromXml(TiXmlHandle rootHandle) {
    TiXmlHandle optionsHandle = rootHandle.FirstChild( TAG_OPTIONS_CONTAINER );
    if(!optionsHandle.ToElement()) throw MissingTagError( TAG_OPTIONS_CONTAINER );

    TiXmlElement * logLevelEl = optionsHandle.FirstChild( TAG_OPTIONS_LOG_LEVEL ).ToElement();
    if(logLevelEl) std::istringstream( logLevelEl->GetText() ) >> logLevel;
    else         Utils::ReportTagMissing( TAG_OPTIONS_LOG_FILENAME , logLevel);


    // TO BE IMPLEMENTED

    //TiXmlElement * logPath = optionsHandle.FirstChild( TAG_OPTIONS_LOG_PATH ).ToElement();
    //if(logPath) this->logPath = logPath->GetText();
    //else        Utils::ReportTagMissing( TAG_OPTIONS_LOG_FILENAME , this->logLevel);

    //TiXmlElement * logFileName = optionsHandle.FirstChild( TAG_OPTIONS_LOG_FILENAME ).ToElement();
    //if(logFileName) this->logFileName = logFileName->GetText();

    return true;
}
