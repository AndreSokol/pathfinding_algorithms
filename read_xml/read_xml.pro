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
    map.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../tinyxml/tinystr.h \
    ../tinyxml/tinyxml.h \
    ../tinyxml/map.h \
    map.h
