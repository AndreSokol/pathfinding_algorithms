#include "gl_settings.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: .exe <filePath>" << std::endl;
        return 0;
    }
    XMLObject new_map;

    /*LOG_FILE_NAME = argv[1] + "_log.txt";
    LOG_PATH = 1;*/

    try {
        new_map.LoadFromFile(argv[1]);
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

    new_map.AnalyzeMap();
    std::cout << new_map;
    new_map.DumpToFile();

    return 0;
}

/*
 * TO-DO list
 *
 * - apply DRY to DumpToXml and GetFromXml functions
 * - implement extended log with process statuses
 *
 */
