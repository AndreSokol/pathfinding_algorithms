#include "astarpathfinder.h"
#include <cmath>
#include <unordered_map>

AstarPathfinder::AstarPathfinder()
{
    start = Utils::Coords(0, 0);
    finish = Utils::Coords(0, 0);
    map = NULL;
}

AstarPathfinder::AstarPathfinder(Utils::Coords start, Utils::Coords finish, Map * map) {
    this->start = start;
    this->finish = finish;
    this->map = map;
}

void AstarPathfinder::InitializeSearch()
{
    auto cmp = [&](Utils::CoordsContainer a, Utils::CoordsContainer b) {return F(a) > F(b);};
        std::priority_queue<Utils::CoordsContainer,
                            std::vector<Utils::CoordsContainer>,
                            decltype(cmp)> open(cmp);

    std::unordered_map<Utils::Coords,Utils::Coords> closed;

    ExecuteSearch(open, closed);
}

double AstarPathfinder::F(Utils::CoordsContainer a)
{
    return (double)a.distance + H(a);
}

double AstarPathfinder::H(Utils::CoordsContainer a)
{
    return sqrt((a.coords.x - finish.x)*(a.coords.x - finish.x) + (a.coords.y - finish.y)*(a.coords.y - finish.y));
}
