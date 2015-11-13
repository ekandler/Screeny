TEMPLATE = app

QT += qml quick
CONFIG += c++11

QMAKE_CXXFLAGS = -fpermissive

LIBS += -lX11 -lXrandr -lstdc++

SOURCES += main.cpp \
    screenmodemanipulatorlinux.cpp \
    screenmodemanipulatorfactory.cpp \
    screen.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    iscreenmodemanipulator.h \
    screenmode.h \
    screenmodemanipulatorlinux.h \
    screenmodemanipulatorfactory.h \
    screen.h \
    xrandr.h

