#ifndef THETASTAR_H
#define THETASTAR_H

#include "astar.h"

class ThetaStar : public Astar
{
public:
    ThetaStar(double w, int BT, int SL);


    bool lineOfSight(const Node &a, const Node &b, const Map &map);
protected:
    void updateParent(Node &node, const Node &start, const Map &map);
    void calculateHeuristic(Node &a, const Map &map, const EnvironmentOptions &options);
};

#endif // THETASTAR_H
