#ifndef BASEPATHFINDER_H
#define BASEPATHFINDER_H

#include "../utils.h"
#include "../map.h"
#include <chrono>
#include <ctime>

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

    std::vector<Utils::Coords> founded_path;
    double elapsed_exec_time;

    template<typename OT, typename CT>
    void ExecuteSearch(OT & open, CT &closed)
    {
        open.push(Utils::CoordsContainer(start, start, 0));

        std::chrono::time_point<std::chrono::system_clock> start_time, end_time;
        start_time = std::chrono::system_clock::now();

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


        end_time = std::chrono::system_clock::now();
        elapsed_exec_time = std::chrono::duration<double>(end_time - start_time).count();

        LoggerInterface logger;

        if(current_point.coords != finish) logger << "[SEARCH] No way found!" << std::endl;
        else {
            Utils::Coords way_point = finish;
            while(way_point != start) {
                founded_path.push_back(way_point);
                way_point = closed[way_point];
            }
            founded_path.push_back(start);

            reverse(founded_path.begin(), founded_path.end());

        }

        logger << "[SEARCH] Elapsed time: " << elapsed_exec_time << "s" << std::endl;
        logger << "[SEARCH] 'Closed' size: " << closed.size() << std::endl;
        logger << "[SEARCH] 'Open' size: " << open.size() << std::endl;
        logger << "[SEARCH] Way length: " << founded_path.size() << std::endl;
    }


public:
    BasePathfinder();
    BasePathfinder(Utils::Coords, Utils::Coords, Map *);

    virtual void InitializeSearch();

    TiXmlElement* DumpLogToXml();
};

#endif // BASEPATHFINDER_H
