#La sortie de la compilation sera un executable
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

DESTDIR = $${DBGNAME}

QT += xml opengl
LIBS += -lqglviewer-qt4 -L./../core/$${DBGNAME}/ -lcore
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ..
DEPENDPATH += .. #check si les fichiers ont été modifiés

HEADERS += 
SOURCES += main.cpp test_fluide.cpp test_materiau.cpp test_noyauLissage.cpp test_particules.cpp test_vecteur.cpp test_map.cpp test_premier.cpp
