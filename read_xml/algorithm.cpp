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

    TiXmlElement * algoType = algoHandle.FirstChild( TAG_ALGO_TYPE ).ToElement();
    if(algoType) this->searchType = algoType->GetText();
    else         Utils::ReportTagMissing( TAG_ALGO_TYPE , this->searchType);

    TiXmlElement * algoMetric = algoHandle.FirstChild( TAG_ALGO_METRIC ).ToElement();
    if(algoMetric) this->metricType = algoMetric->GetText();
    else           Utils::ReportTagMissing( TAG_ALGO_METRIC , this->metricType);

    TiXmlElement * algoHweight = algoHandle.FirstChild( TAG_ALGO_HWEIGHT ).ToElement();
    if(algoHweight) std::istringstream(algoHweight->GetText()) >> this->hWeight;
    else            Utils::ReportTagMissing( TAG_ALGO_HWEIGHT , this->hWeight);

    TiXmlElement * algoTieBreak = algoHandle.FirstChild( TAG_ALGO_TIE_BRAKE ).ToElement();
    if(algoTieBreak) this->breakingTies = algoTieBreak->GetText();
    else             Utils::ReportTagMissing( TAG_ALGO_TIE_BRAKE , this->breakingTies);

    TiXmlElement * algoLineCost = algoHandle.FirstChild( TAG_ALGO_LINE_COST ).ToElement();
    if(algoLineCost) std::istringstream(algoLineCost->GetText()) >> this->lineCost;
    else             Utils::ReportTagMissing( TAG_ALGO_LINE_COST , this->lineCost);

    TiXmlElement * algoDiagCost = algoHandle.FirstChild( TAG_ALGO_DIAG_COST ).ToElement();
    if(algoDiagCost) std::istringstream(algoDiagCost->GetText()) >> this->diagonalCost;
    else             Utils::ReportTagMissing( TAG_ALGO_DIAG_COST , this->diagonalCost);

    TiXmlElement * algoAllowDiag = algoHandle.FirstChild( TAG_ALGO_ALLOW_DIAG ).ToElement();
    if(algoAllowDiag) std::istringstream(algoAllowDiag->GetText()) >> this->allowDiagonal;
    else              Utils::ReportTagMissing( TAG_ALGO_ALLOW_DIAG , this->allowDiagonal);

    TiXmlElement * algoAllowSqueeze = algoHandle.FirstChild( TAG_ALGO_ALLOW_SQUEEZE ).ToElement();
    if(algoAllowSqueeze) std::istringstream(algoAllowSqueeze->GetText()) >> this->allowSqueeze;
    else                 Utils::ReportTagMissing( TAG_ALGO_ALLOW_SQUEEZE , this->allowSqueeze);

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
