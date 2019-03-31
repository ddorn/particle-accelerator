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
    ../header/Support.h \
    ../header/Content.h \
    ../header/constants.h \
    ../header/Accelerator.h \
    ../header/Vector3D.h \
    ../header/Element.h \
    ../header/Particle.h \
	../header/CurvedElement.h \
	../header/StraightElement.h \
	../header/Segment.h


RESOURCES += resources.qrc
