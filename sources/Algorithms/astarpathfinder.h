#ifndef ASTARPATHFINDER_H
#define ASTARPATHFINDER_H

#include "../utils.h"
#include "basepathfinder.h"
#include <cmath>

class AstarPathfinder : public BasePathfinder
{
public:
    AstarPathfinder();
    AstarPathfinder(Utils::Coords, Utils::Coords, Map *);
    void InitializeSearch();
protected:
    double F(Utils::CoordsContainer);
    double H(Utils::CoordsContainer);
};

#endif // ASTARPATHFINDER_H
