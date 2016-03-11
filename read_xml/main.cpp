#include "gl_settings.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: .exe <filePath>" << std::endl;
        return 0;
    }
    Map new_map;

    try {
        new_map.GetMapFromXML(argv[1]);
    }
    catch (MissingTagError e) {
        std::cerr << "[ERROR] Cannot find nessecary tag <" << e.tag() << ">! Exiting programm..." << std::endl;
        return EXIT_FAILURE;
    }
    catch (ParserError e) {
        std::cerr << "[ERROR] During reading file:" << std::endl
                  << "[.....] " << e.path() << std::endl
                  << "[.....] tinyXML parser caught following error: "
                  << e.msg() << std::endl;
        return EXIT_FAILURE;
    }

    Analysis analysis;

    analysis.AnalyzeMap(&new_map);

    std::cout << analysis;

    new_map.DumpToXML("out.xml");

    return 0;
}

