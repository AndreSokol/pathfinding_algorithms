#include "gl_settings.h"
#include "xmlobject.h"
#include "logger.h"
#include "errors.cpp"

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 4) {
        std::cerr << "Usage: .exe <filePath> [-l <logPath>]" << std::endl;
        return 0;
    }

    LoggerInterface logger;

    XMLObject new_map(argv[1]);

    if (argc == 4) {
        if (argv[2] != std::string("-l")) {
            std::cerr << "Usage: .exe <filePath> [-l <logPath>]" << std::endl;
            return 0;
        }

        logger.SetLogPath(argv[3]);
    }
    else {
        logger << "[WARNING] No logs location specified; logs will be saved to default loaction '" <<
                       logger.LogPath() << "'" << std::endl;
    }

    logger << "test";
    logger << "test";

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
    new_map.DumpToFile();

    new_map.FindPath();

    return 0;
}
