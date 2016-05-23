TEMPLATE = app
CONFIG += console
CONFIG += static
#CONFIG += static_runtime
#CONFIG -= app_bundle
CONFIG -= qt
#CONFIG -= threads
#CONFIG -= spec
DEFINES -= UNICODE QT_LARGEFILE_SUPPORT
#CONFIG += address_sanitizer
#QMAKE_CXXFLAGS += -fsanitize=address
#QMAKE_CXXFLAGS += -fno-omit-frame-pointer
#QMAKE_CFLAGS += -fsanitize=address
#QMAKE_CFLAGS += -fno-omit-frame-pointer
#QMAKE_LFLAGS += -fsanitize=address


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
    logger.cpp \
    xmlobject.cpp

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
    logger.h \
    xmlobject.h

DISTFILES += \
    Logic/TagNecessity.txt
