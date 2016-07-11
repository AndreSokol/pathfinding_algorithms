#include "astar.h"
#include <set>
#include "orderedvector.h"
#include <chrono>

Astar::Astar(double w, int BT, int SL)
{
    hweight = w;
    breakingties = BT;
    sizelimit = SL;
}

Astar::~Astar()
{
}

SearchResult Astar::startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options)
{
    std::set<Node> closed;

    auto cmp = [&](const Node & a, const Node & b) {return a.F < b.F;};
    OrderedVector<Node, decltype(&cmp)> open(&cmp);

    auto start_time = std::chrono::system_clock::now();

    Node start;
    start.i = Map.start_i;
    start.j = Map.start_j;
    start.g = 0;

    Node goal;
    goal.i = Map.goal_i;
    goal.j = Map.goal_j;

    open.push(start);

    sresult.pathfound = false;
    sresult.numberofsteps = 0;

    Node current_node, new_node;
    bool is_diagonal;
    while (!open.empty()) {
        current_node = open.pop();
        if (closed.count(current_node) != 0) continue;
        closed.insert(current_node);

        //std::cout << current_node.i << " " << current_node.j << std::endl;

        /*Node x, y;
        x.i = 0;
        x.j = 1;
        y.i = x.i;
        y.j = x.j;
        std::cout << (x == y) << std::endl;*/


        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;

                if (i * j != 0) { // this means i != 0 and j != 0
                    if (options.allowdiagonal == 0) continue;
                    is_diagonal = true;
                }
                else {
                    is_diagonal = false;
                }

                new_node.i = current_node.i + i;
                new_node.j = current_node.j + j;

                if (!Map.CellOnGrid(new_node.i, new_node.j)) continue;
                if (Map.CellIsObstacle(new_node.i, new_node.j)) continue;
                if (closed.count(new_node) != 0) continue;
                if (is_diagonal)
                    if (!options.allowsqueeze &&
                            (Map.CellIsObstacle(new_node.i, current_node.j) || Map.CellIsObstacle(current_node.i, new_node.j)))
                                    continue;

                new_node.parent_i = current_node.i;
                new_node.parent_j = current_node.j;

                if (is_diagonal)
                    new_node.g = current_node.g + options.diagonalcost;
                else
                    new_node.g = current_node.g + options.linecost;

                calculateHeuristic(new_node, Map, options);

                open.push(new_node);

                if(new_node == goal) {
                    std::cerr << "lol" << std::endl;
                    sresult.pathfound = true;
                    break;
                }
            }
            if(sresult.pathfound) break;
        }
        sresult.numberofsteps++;
        if(sresult.pathfound) break;
    }

    auto end_time = std::chrono::system_clock::now();
    sresult.time = (std::chrono::duration<double>(end_time - start_time)).count();

    sresult.nodescreated = open.size() + closed.size();

    if (sresult.pathfound) {
        sresult.pathlength = 0;

        current_node = new_node;
        Node temp;

        sresult.lppath = new NodeList();
        sresult.hppath = new NodeList();

        while (!(current_node == start)) {
            //std::cout << "T" << std::endl;

            sresult.lppath->push_front(current_node);
            sresult.hppath->push_front(current_node);
            sresult.pathlength++;

            temp.i = current_node.parent_i;
            temp.j = current_node.parent_j;
            current_node = *(closed.find(temp));
        }

        // Adding start node to path
        sresult.lppath->push_front(current_node);
        sresult.hppath->push_front(current_node);
    }
    else {
        sresult.lppath = NULL;
        sresult.hppath = NULL;
        sresult.pathlength = 0;
    }

    /*std::list<Node>::iterator it = sresult.lppath->List.begin();
    std::list<Node>::iterator it_end = sresult.lppath->List.end();
    for(; it != it_end; it++) {
        std::cout << (*it).i << " " << (*it).j << std::endl;
    }*/

    return sresult;
}

void Astar::calculateHeuristic(Node & a, const Map &map, const EnvironmentOptions &options)
{
    a.F = a.g;
    if(options.metrictype == CN_SP_MT_EUCL) a.H = sqrt((a.i - map.goal_i) * (a.i - map.goal_i) + (a.j - map.goal_j) * (a.j - map.goal_j));
    else a.H = 0;

    a.F += hweight * a.H;
}
