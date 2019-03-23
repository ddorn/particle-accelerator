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
    Element.cpp

HEADERS += \
    ../header/Accelerator.h \
    ../header/Vector3D.h \
    ../header/Element.h \
    ../header/Particle.h \
    ../header/constants.h
