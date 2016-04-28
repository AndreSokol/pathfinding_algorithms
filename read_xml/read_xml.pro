TEMPLATE = app
CONFIG += console
CONFIG += static
#CONFIG += static_runtime
#CONFIG -= app_bundle
CONFIG -= qt
#CONFIG -= threads
#CONFIG -= spec
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT

SOURCES += main.cpp \
    ../tinyxml/tinystr.cpp \
    ../tinyxml/tinyxml.cpp \
    ../tinyxml/tinyxmlerror.cpp \
    ../tinyxml/tinyxmlparser.cpp \
    errors.cpp \
    utils.cpp \
    obstacle.cpp \
    algorithm.cpp \
    options.cpp \
    map.cpp \
    mapanalyzer.cpp \
    xmlobject.cpp \
    logger.cpp

HEADERS += \
    ../tinyxml/tinystr.h \
    ../tinyxml/tinyxml.h \
    gl_settings.h \
    utils.h \
    obstacle.h \
    algorithm.h \
    options.h \
    map.h \
    mapanalyzer.h \
    xmlobject.h \
    logger.h

DISTFILES += \
    Logic/TagNecessity.txt
