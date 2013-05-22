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

HEADERS += 
SOURCES += 

