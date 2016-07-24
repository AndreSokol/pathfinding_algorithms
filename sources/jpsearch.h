#ifndef JPSEARCH_H
#define JPSEARCH_H

#include "isearch.h"
#include "ilogger.h"
#include "map.h"
#include "environmentoptions.h"

class JPSearch : public ISearch
{
public:
    JPSearch(double weight, int BT, int SL);
    SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options);

private:
    std::pair<bool, Node> jump(const Node &node, int di, int dj, const Map &map, const Node &goal);
    void calculateHeuristic(Node &a, const Map &map, const EnvironmentOptions &options);
};

#endif // JPSEARCH_H
