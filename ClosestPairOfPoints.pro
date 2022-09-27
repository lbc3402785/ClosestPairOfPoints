QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
OBJECTS_DIR=$${PWD}/build
QMAKE_CXXFLAGS += /bigobj
HEADERS += \
    DivideAndConquer2D.h \
    RandomizedIncrementalD.h \
    basic.h \
    test.h

SOURCES += \
    main.cpp \
    test.cpp
