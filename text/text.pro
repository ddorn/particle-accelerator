CONFIG += c++17
QT =

TARGET = text_accelerator
DESTDIR = ../bin
OBJECTS_DIR = ../obj

INCLUDEPATH = ../header
LIBS += -L../bin -lsrc
# PRE_TARGETDEPS += ../bin/libsrc.a

SOURCES += \
    main.cpp \
    TextSupport.cpp


HEADERS += \
    ../header/TextSupport.h \
    ../header/Support.h \
    ../header/Content.h \
    ../header/Accelerator.h \
    ../header/Vector3D.h \
    ../header/Element.h \
    ../header/Particle.h \
    ../header/constants.h
