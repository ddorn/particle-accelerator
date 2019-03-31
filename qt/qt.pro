CONFIG += c++17
QT += core gui opengl widgets

TARGET = qt_accelerator
DESTDIR = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH = ../header
LIBS += -L../bin -lsrc
win32:LIBS += -lopengl32
# PRE_TARGETDEPS += ../bin/libsrc.a


SOURCES += \
    qt_main.cpp \
    QtSupport.cpp \
    GlWidget.cpp \
    GlSphere.cpp

HEADERS += \
    ../header/QtSupport.h \
    ../header/GlWidget.h \
    ../header/GlSphere.h \
	../header/all.h


RESOURCES += resources.qrc
