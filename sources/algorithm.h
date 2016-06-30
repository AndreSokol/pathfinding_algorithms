#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "gl_settings.h"

class Algorithm {
public:
    Algorithm(TiXmlHandle, Logger*);
    ~Algorithm();

    friend std::ostream& operator<< (std::ostream &, const Algorithm &);

    TiXmlElement* DumpToXmlElement();
private:
    std::string searchType;
    std::string metricType;
    double hWeight;
    std::string breakingTies;
    double lineCost;
    double diagonalCost;
    bool allowDiagonal;
    bool allowSqueeze;
    Logger *logger;

    bool GetDataFromXml(TiXmlHandle);
};
#endif // ALGORITHM_H
