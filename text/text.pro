CONFIG += c++17

TARGET = text_accelerator

INCLUDEPATH = ../header

SOURCES += \
    main.cpp \
    TextSupport.cpp \
	../src/Accelerator.cpp \
	../src/CurvedElement.cpp \
	../src/Element.cpp \
	../src/Particle.cpp \
	../src/Vector3D.cpp

DESTDIR = ../bin
OBJECTS_DIR = ../obj

HEADERS += \
    ../header/TextSupport.h \
    ../header/Support.h \
    ../header/Content.h \
    ../header/Accelerator.h \
    ../header/Vector3D.h \
    ../header/Element.h \
    ../header/Particle.h \
    ../header/constants.h
