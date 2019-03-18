CONFIG += c++17
QT += core gui opengl widgets

TARGET = qt_accelerator
DESTDIR = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH = ../header ../bin
LIBS += -L../src -lsrc
win32:LIBS += -lopengl32
PRE_TARGETDEPS += ../bin/libsrc.a


SOURCES += \
    qt_main.cpp \
    QtSupport.cpp \
    GlWidget.cpp

HEADERS += \
    ../header/QtSupport.h \
    ../header/GlWidget.h \
    ../header/Support.h \
    ../header/Content.h \
    ../header/Accelerator.h \
    ../header/Vector3D.h \
    ../header/Element.h \
    ../header/Particle.h \
    ../header/constants.h

RESOURCES += resources.qrc
