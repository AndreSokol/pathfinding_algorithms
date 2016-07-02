TEMPLATE = app
CONFIG += console
CONFIG += static
CONFIG -= qt
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT
CONFIG += c++14

SOURCES += main.cpp \
    ../tinyxml/tinystr.cpp \
    ../tinyxml/tinyxml.cpp \
    ../tinyxml/tinyxmlerror.cpp \
    ../tinyxml/tinyxmlparser.cpp \
    errors.cpp \
    utils.cpp \
    obstacle.cpp \
    options.cpp \
    map.cpp \
    mapanalyzer.cpp \
    logger.cpp \
    xmlobject.cpp \
    pathfindingtask.cpp \
    algorithms/basepathfinder.cpp \
    algorithms/astarpathfinder.cpp \
    structures/minqueue.cpp

HEADERS += \
    ../tinyxml/tinystr.h \
    ../tinyxml/tinyxml.h \
    gl_settings.h \
    utils.h \
    obstacle.h \
    options.h \
    map.h \
    mapanalyzer.h \
    logger.h \
    xmlobject.h \
    pathfindingtask.h \
    algorithms/basepathfinder.h \
    algorithms/astarpathfinder.h \
    structures/minqueue.h

DISTFILES += \
    Logic/TagNecessity.txt
