QT =
TEMPLATE = lib
TARGET = src

CONFIG += staticlib c++14
INCLUDEPATH = ../header

DESTDIR = ../bin
OBJECTS_DIR = ../obj

SOURCES = \
    Accelerator.cpp \
    Beam.cpp \
    CircularBeam.cpp \
    Dipole.cpp \
    Particle.cpp \
    Vector3D.cpp \
    Element.cpp \
    CurvedElement.cpp \
    StraightElement.cpp \
	Segment.cpp \
	Sextupole.cpp \
	Quadrupole.cpp \
	Node.cpp

HEADERS += all.h
