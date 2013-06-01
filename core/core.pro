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
QMAKE_CXXFLAGS += -std=c++0x

HEADERS += fluide.hpp materiau.hpp noyauLissage.hpp particule.hpp vecteur.hpp premier.hpp
SOURCES +=

