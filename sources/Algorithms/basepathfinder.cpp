#include "basepathfinder.h"
#include "../map.h"
#include "../utils.h"
#include <unordered_map>

BasePathfinder::BasePathfinder()
{
    start = Utils::Coords(0, 0);
    finish = Utils::Coords(0, 0);
    map = NULL;
}

BasePathfinder::BasePathfinder(Utils::Coords start, Utils::Coords finish, Map * map) {
    this->start = start;
    this->finish = finish;
    this->map = map;
}

void BasePathfinder::InitializeSearch() {
    auto cmp = [&](Utils::CoordsContainer a, Utils::CoordsContainer b) {return F(a) > F(b);};
        std::priority_queue<Utils::CoordsContainer,
                            std::vector<Utils::CoordsContainer>,
                            decltype(cmp)> open(cmp);

    std::unordered_map<Utils::Coords,Utils::Coords> closed;

    ExecuteSearch(open, closed);
}
