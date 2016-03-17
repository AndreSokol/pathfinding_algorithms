TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
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
    mapanalyzer.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../tinyxml/tinystr.h \
    ../tinyxml/tinyxml.h \
    ../tinyxml/map.h \
    gl_settings.h \
    utils.h \
    obstacle.h \
    algorithm.h \
    options.h \
    map.h \
    mapanalyzer.h

DISTFILES += \
    Logic/TagNecessity.txt
