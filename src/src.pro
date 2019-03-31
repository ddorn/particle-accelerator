QT =
TEMPLATE = lib
TARGET = src

CONFIG = staticlib c++17
INCLUDEPATH = ../header

DESTDIR = ../bin
OBJECTS_DIR = ../obj

SOURCES = \
    Accelerator.cpp \
    Particle.cpp \
    Vector3D.cpp \
    Element.cpp \
    CurvedElement.cpp \
    StraightElement.cpp \
	Segment.cpp

HEADERS += \
    ../header/constants.h \
    ../header/Accelerator.h \
    ../header/Vector3D.h \
    ../header/Particle.h \
    ../header/Element.h \
    ../header/CurvedElement.cpp \
	../header/StraightElement.h \
	../header/Segment.h
