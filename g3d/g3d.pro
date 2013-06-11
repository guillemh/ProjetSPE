TEMPLATE = app
TARGET   = test_dessin_fluide
CONFIG  += qt opengl glut warn_on thread openmp debug # release 
QT *= xml opengl 
QMAKE_CFLAGS += -O3
QMAKE_CXXFLAGS += -std=c++0x -O3

HEADERS  = viewer.h scene.h ../core/metaballs.hpp
SOURCES  = main.cpp viewer.cpp scene.cpp ../core/metaballs.cpp
LIBS *= -lglut

exists( /usr/lib/libqglviewer-qt4.so) |
exists( /usr/lib/x86_64-linux-gnu/libqglviewer-qt4.so )
{
  LIBS *= -lqglviewer-qt4
} else {
  LIBS *= -lqglviewer
}
