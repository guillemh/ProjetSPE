TEMPLATE = app

CXXFLAGS = -g -Wall -std=c++0x

#Creation de deux dossiers debug / release selon la compilation choisie
CONFIG += debug_and_release
CONFIG(release, debug|release){
    DBGNAME = release
}
else {
    DBGNAME = debug
}

#CONFIG  += qt opengl glut warn_on thread openmp debug # release 

DESTDIR = $${DBGNAME}

QT *= xml opengl 
QMAKE_CFLAGS += -O3
QMAKE_CXXFLAGS += -std=c++0x -O3

HEADERS  = viewerCascade.h sceneCascade.h skybox.h cascade.hpp 
SOURCES  = main.cpp viewerCascade.cpp sceneCascade.cpp skybox.cpp ../core/metaballs.cpp
LIBS += -lglut
LIBS += -lqglviewer-qt4 -L./../core/$${DBGNAME}/ -lcore

INCLUDEPATH += .. 
DEPENDPATH += .. #check si les fichiers ont été modifiés

exists( /usr/lib/libqglviewer-qt4.so) |
exists( /usr/lib/x86_64-linux-gnu/libqglviewer-qt4.so )
{
  LIBS *= -lqglviewer-qt4
} else {
  LIBS *= -lqglviewer
}
