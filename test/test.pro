CONFIG += c++14
QT =

TARGET = test_vector
DESTDIR = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH = ../header
LIBS += -L../bin -lsrc
# PRE_TARGETDEPS += ../bin/libsrc.a

SOURCES += \
    test_vector3d.cpp \
    ../text/TextSupport.cpp


HEADERS += \
    ../header/TextSupport.h \
	../header/all.h
