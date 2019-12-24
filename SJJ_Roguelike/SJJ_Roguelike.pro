TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "C:\pdcurses"

SOURCES += main.cpp \
    roguelikefunctions.cpp \
    rogue.cpp \
    screenobject.cpp \
    character.cpp \
    obstacle.cpp \
    elf.cpp \
    ogre.cpp \
    dragon.cpp

LIBS += -L"C:\pdcurses" -lpdcurses

HEADERS += \
    roguelikefunctions.h \
    rogue.h \
    screenobject.h \
    character.h \
    coordinateyx.h \
    enemy.h \
    obstacle.h \
    elf.h \
    ogre.h \
    dragon.h
