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
	Segment.cpp \
	Quadrupole.cpp

HEADERS += all.h
