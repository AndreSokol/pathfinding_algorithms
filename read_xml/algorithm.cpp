#include "algorithm.h"
#include "gl_settings.h"

Algorithm::Algorithm(TiXmlHandle rootHandle) {
    searchType = "astar";
    metricType = "euclid";
    hWeight = 1.0;
    breakingTies = "gmax";
    lineCost = 1.0;
    diagonalCost = 1.414;
    allowDiagonal = false;
    allowSqueeze = false;

    GetDataFromXml(rootHandle);
}

bool Algorithm::GetDataFromXml(TiXmlHandle rootHandle) {
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
    TiXmlElement* root = new TiXmlElement( TAG_ALGO_CONTAINER );

    TiXmlElement* searchTypeEl = new TiXmlElement( TAG_ALGO_TYPE );
    searchTypeEl->LinkEndChild(new TiXmlText(this->searchType));
    root->LinkEndChild(searchTypeEl);

    TiXmlElement* metricTypeEl = new TiXmlElement( TAG_ALGO_METRIC );
    metricTypeEl->LinkEndChild(new TiXmlText(this->metricType));
    root->LinkEndChild(metricTypeEl);

    TiXmlElement* hweightEl = new TiXmlElement( TAG_ALGO_HWEIGHT );
    hweightEl->LinkEndChild(new TiXmlText( Utils::toString(this->hWeight) ));
    root->LinkEndChild(hweightEl);

    TiXmlElement* breakingTiesEl = new TiXmlElement( TAG_ALGO_TIE_BRAKE );
    breakingTiesEl->LinkEndChild(new TiXmlText(this->breakingTies));
    root->LinkEndChild(breakingTiesEl);

    TiXmlElement* lineCostEl = new TiXmlElement( TAG_ALGO_LINE_COST );
    lineCostEl->LinkEndChild(new TiXmlText( Utils::toString(this->lineCost) ));
    root->LinkEndChild(lineCostEl);

    TiXmlElement* diagonalCostEl = new TiXmlElement( TAG_ALGO_DIAG_COST );
    diagonalCostEl->LinkEndChild(new TiXmlText( Utils::toString(this->diagonalCost) ));
    root->LinkEndChild(diagonalCostEl);

    TiXmlElement* allowDiagonalEl = new TiXmlElement( TAG_ALGO_ALLOW_DIAG );
    allowDiagonalEl->LinkEndChild(new TiXmlText( Utils::toString(this->allowDiagonal) ));
    root->LinkEndChild(allowDiagonalEl);

    TiXmlElement* allowSqueezeEl = new TiXmlElement( TAG_ALGO_ALLOW_SQUEEZE );
    allowSqueezeEl->LinkEndChild(new TiXmlText( Utils::toString(this->allowSqueeze) ));
    root->LinkEndChild(allowSqueezeEl);

    return root;
}
