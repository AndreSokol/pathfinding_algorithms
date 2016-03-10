#include "gl_settings.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: .exe <filePath>" << std::endl;
        return 0;
    }
    Map new_map;

    if(!new_map.GetMapFromXML(argv[1])) {
        std::cerr << "Error: cannot read file" << std::endl;
        return 0;
    }

    Analysis analysis;

    analysis.AnalyzeMap(&new_map);

    std::cout << analysis;

    //std::cout << "Density: " << new_map.CalculateDensity() << std::endl;

    new_map.DumpToXML("out.xml");

    return 0;
}

