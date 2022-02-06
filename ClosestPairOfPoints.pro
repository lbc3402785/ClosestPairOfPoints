QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
OBJECTS_DIR=$${PWD}/build
QMAKE_CXXFLAGS += /bigobj
HEADERS += \
    DivideAndConquer2D.h \
    RandomizedIncremental2D.h \
    basic.h \
    test.h

SOURCES += \
    main.cpp \
    test.cpp
