TEMPLATE = lib

CXXFLAGS = -g -Wall

CONFIG += debug_and_release
CONFIG(release, debug|release){
    DBGNAME = release
}
else {
    DBGNAME = debug
}

DESTDIR = $${DBGNAME}

QT += xml opengl
QMAKE_CFLAGS += -O3
QMAKE_CXXFLAGS += -std=c++0x -O3

HEADERS += fluide.hpp materiau.hpp noyauLissage.hpp particule.hpp vecteur.hpp premier.hpp metaballs.hpp
SOURCES += metaballs.cpp

