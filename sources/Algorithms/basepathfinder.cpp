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

TiXmlElement* BasePathfinder::DumpLogToXml()
{
    // This need to be beatified later
    //logger << "[INFO] Dumping search results to XML..." << std::endl;

    TiXmlElement* resultsContainer = new TiXmlElement( "log" );

    resultsContainer->LinkEndChild(Utils::dumpValueToXmlNode("", "mapfilename"));

    TiXmlElement* summaryEl = new TiXmlElement( "summary" );
    summaryEl->SetAttribute("numberofsteps", 0);
    summaryEl->SetAttribute("nodescreated", 0);
    summaryEl->SetAttribute("length", founded_path.size());
    summaryEl->SetAttribute("time", elapsed_exec_time);

    resultsContainer->LinkEndChild(summaryEl);

    TiXmlElement* lplevelContainer = new TiXmlElement( "lplevel" );

    for(unsigned int i = 0; i < founded_path.size(); i++) {
        TiXmlElement* newNode = new TiXmlElement("node");
        newNode->SetAttribute("x", founded_path[i].x);
        newNode->SetAttribute("y", founded_path[i].y);
        newNode->SetAttribute("number", i);
        lplevelContainer->LinkEndChild(newNode);
    }

    resultsContainer->LinkEndChild(lplevelContainer);
    resultsContainer->LinkEndChild(Utils::dumpValueToXmlNode("", "hplevel"));

    return resultsContainer;
}
