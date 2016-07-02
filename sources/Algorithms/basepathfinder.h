#ifndef BASEPATHFINDER_H
#define BASEPATHFINDER_H

#include "../utils.h"
#include "../map.h"
#include <functional>

typedef std::function<bool(const Utils::CoordsContainer &, const Utils::CoordsContainer &)> CmpType;

class BasePathfinder
{
protected:
    /*
     * We take Dijkstra search as the base search for this project
     */
    virtual double F(const Utils::CoordsContainer & container) {
        return container.distance;
    }

    Utils::Coords start;
    Utils::Coords finish;

    Map * map;

    template<typename OpenType, typename ClosedType>
    void ExecuteSearch(OpenType & open, ClosedType &closed)
    {
        open.push(Utils::CoordsContainer(start, start, 0));

        Utils::CoordsContainer current_point, next_point;
        while(!open.empty() && current_point.coords != finish) {
            current_point = open.top();
            open.pop();

            if (closed.count(current_point.coords) != 0) continue;

            for (int i = 0; i < 4; i++) {
                next_point = Utils::CoordsContainer(current_point.coords + Utils::NEIGHBOURS_NO_DIAG[i],
                                                    current_point.coords,
                                                    current_point.distance + 1);
                if(map->At(next_point.coords) == INPUT_FREE_CELL && closed.count(next_point.coords) == 0) {
                    open.push(next_point);
                }
            }

            closed[current_point.coords] = current_point.prev_coords;
        }

        if(current_point.coords != finish) std::cout << "No way found" << std::endl;
        else {
            std::vector<Utils::Coords> way;

            Utils::Coords way_point = finish;
            while(way_point != start) {
                way.push_back(way_point);
                way_point = closed[way_point];
            }
            way.push_back(start);

            reverse(way.begin(), way.end());

            std::cout << "### Search results ###" << std::endl;
            std::cout << "'Closed' size: " << closed.size() << std::endl;
            std::cout << "'Open' size: " << open.size() << std::endl;
            std::cout << "Way length: " << way.size() << std::endl;
            /*std::cout << "Way by coordinates:" << std::endl;
            for(unsigned int i = 0; i < way.size(); i++) {
                std::cout << i << "  (" << way[i].x << ", " << way[i].y << ")" <<
                          this->F(Utils::CoordsContainer(way[i], way[i], 0)) << std::endl;
            }*/
        }
    }

public:
    BasePathfinder();
    BasePathfinder(Utils::Coords, Utils::Coords, Map *);

    virtual void InitializeSearch();

};

#endif // BASEPATHFINDER_H
