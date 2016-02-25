#include "gl_settings.h"
#include "map.cpp"

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

    //std::cout << new_map;

    new_map.DumpToXML("out.xml");

    return 0;
}

