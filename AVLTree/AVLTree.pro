TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
QMAKE_CXXFLAGS += -std=c++11

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    AVLTree.h \
    AVLNode.h

