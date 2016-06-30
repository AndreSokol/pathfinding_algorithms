#include "algorithm.h"
#include "gl_settings.h"

Algorithm::Algorithm(TiXmlHandle rootHandle, Logger* logger) {
    searchType = "astar";
    metricType = "euclid";
    hWeight = 1.0;
    breakingTies = "gmax";
    lineCost = 1.0;
    diagonalCost = 1.414;
    allowDiagonal = false;
    allowSqueeze = false;
    this->logger = logger;

    GetDataFromXml(rootHandle);
}

bool Algorithm::GetDataFromXml(TiXmlHandle rootHandle) {
    *logger << "[INFO] Reading algorithm settings from XML..." << std::endl;
    TiXmlHandle algoHandle = rootHandle.FirstChild( TAG_ALGO_CONTAINER );
    if(!algoHandle.ToElement()) throw MissingTagError( TAG_ALGO_CONTAINER );

    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_TYPE , searchType);
    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_METRIC , metricType);
    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_HWEIGHT , hWeight);
    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_TIE_BRAKE , breakingTies);
    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_LINE_COST, lineCost);
    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_DIAG_COST, diagonalCost);
    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_ALLOW_DIAG , allowDiagonal);
    Utils::parseValueFromXmlNode(algoHandle, TAG_ALGO_ALLOW_SQUEEZE , allowSqueeze);

    *logger << "[INFO] Reading algorithm settings done!" << std::endl;

    return true;
}

Algorithm::~Algorithm() {
    // to be implemented
}

std::ostream& operator<< (std::ostream &os, const Algorithm& algo) {
    os << algo.searchType << " in " << algo.metricType << " metric" << std::endl;
    os << algo.diagonalCost << std::endl;
    return os;
}

TiXmlElement* Algorithm::DumpToXmlElement() {
    *logger << "[INFO] Dumping algorithm settings to XML..." << std::endl;
    TiXmlElement* root = new TiXmlElement( TAG_ALGO_CONTAINER );

    root->LinkEndChild(Utils::dumpValueToXmlNode(searchType, TAG_ALGO_TYPE));
    root->LinkEndChild(Utils::dumpValueToXmlNode(metricType, TAG_ALGO_METRIC));
    root->LinkEndChild(Utils::dumpValueToXmlNode(hWeight, TAG_ALGO_HWEIGHT));
    root->LinkEndChild(Utils::dumpValueToXmlNode(breakingTies, TAG_ALGO_TIE_BRAKE));
    root->LinkEndChild(Utils::dumpValueToXmlNode(lineCost, TAG_ALGO_LINE_COST));
    root->LinkEndChild(Utils::dumpValueToXmlNode(diagonalCost, TAG_ALGO_DIAG_COST));
    root->LinkEndChild(Utils::dumpValueToXmlNode(allowDiagonal, TAG_ALGO_ALLOW_DIAG));
    root->LinkEndChild(Utils::dumpValueToXmlNode(allowSqueeze, TAG_ALGO_ALLOW_SQUEEZE));

    *logger << "[INFO] Dumping algorithm settings to XML done!" << std::endl;

    return root;
}
