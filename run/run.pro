TEMPLATE = app

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
LIBS += -L./../core/$${DBGNAME}/ -lcore
#Linking flags
QMAKE_LFLAGS += -Wl,-rpath,./../../core/release/

INCLUDEPATH += ..
DEPENDPATH += .. #check si les fichiers ont été modifiés

HEADERS += viewer.h \
            viewer.hpp \
            mainwindow.h \
            camera.h \
            ../core/vecteur.hpp \
            ../core/particule.hpp \
            ../core/materiau.hpp \
            ../core/premier.hpp \
            ../core/noyauLissage.hpp \
            ../core/fluide.hpp \
            ../core/metaballs.hpp \
            

SOURCES += main.cpp \
            viewer.cpp \
            mainwindow.cpp \
            camera.cpp \
            ../core/metaballs.cpp \
