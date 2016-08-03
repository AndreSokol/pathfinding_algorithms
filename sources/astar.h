#ifndef ASTAR_H
#define ASTAR_H
#include "gl_const.h"
#include "isearch.h"
#include "ilogger.h"
#include <stdlib.h>
#include <math.h>

class Astar : public ISearch
{
    public:
        Astar();
        Astar(double weight, int BT, int SL);
        ~Astar();
        SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options);
        bool F_cmp(Node, Node);

    protected:
        virtual void updateParent(Node &node, const Map &map, const EnvironmentOptions &options);
        virtual void calculateHeuristic(Node &a, const Map &map, const EnvironmentOptions &options);
};

#endif
