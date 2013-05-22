#La sortie de la compilation sera un executable
TEMPLATE = app

CXXFLAGS = -g -Wall

#Creation de deux dossiers debug / release selon la compilation choisie
CONFIG += debug_and_release
CONFIG(release, debug|release){
    DBGNAME = release
}
else {
    DBGNAME = debug
}

DESTDIR = $${DBGNAME}

QT += xml opengl
LIBS += -lqglviewer-qt4 -L./../core/$${DBGNAME}/ -lcore


INCLUDEPATH += ..
DEPENDPATH += .. #check si les fichiers ont été modifiés

HEADERS += 
SOURCES += main.cpp \
