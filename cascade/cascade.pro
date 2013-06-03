TEMPLATE = app
CONFIG  += qt opengl glut warn_on thread openmp debug # release 
QT *= xml opengl 
QMAKE_CXXFLAGS += -std=c++0x

HEADERS  = viewer.h sceneCascade.h
SOURCES  = main.cpp viewer.cpp sceneCascade.cpp
LIBS *= -lglut

exists( /usr/lib/libqglviewer-qt4.so) |
exists( /usr/lib/x86_64-linux-gnu/libqglviewer-qt4.so )
{
  LIBS *= -lqglviewer-qt4
} else {
  LIBS *= -lqglviewer
}
