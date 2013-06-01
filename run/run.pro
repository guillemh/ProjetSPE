TEMPLATE = app
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
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += ..
DEPENDPATH += .. #check si les fichiers ont été modifiés

HEADERS += viewer.h \
            viewer.hpp \
            mainwindow.h \
            camera.h

SOURCES += main.cpp \
            viewer.cpp \
            mainwindow.cpp \
            camera.cpp
