CONFIG += c++14
QT =

TARGET = p10
DESTDIR = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH = ../header
LIBS += -L../bin -lsrc
# PRE_TARGETDEPS += ../bin/libsrc.a

SOURCES += \
    p10.cpp \
    TextSupport.cpp


HEADERS += \
    ../header/TextSupport.h \
	../header/all.h
