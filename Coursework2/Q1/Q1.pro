exists($$PWD/lib/*.cpp){
    SOURCES += $$PWD/lib/*.cpp
}
exists($$PWD/src/*.cpp) {
    SOURCES += $$PWD/src/*.cpp
}
exists($$PWD/*.cpp) {
    SOURCES += $$PWD/*.cpp
}

exists($$PWD/lib/*.h) {
    HEADERS += $$PWD/lib/*.h
}

exists($$PWD/src/*.h) {
    HEADERS += $$PWD/src/*.h
}
exists($$PWD/*.h) {
    HEADERS += $$PWD/*.h
}

# directories examined by Qt Creator when student writes an #include statement
INCLUDEPATH += $$PWD/lib/
INCLUDEPATH += $$PWD/src/
INCLUDEPATH += $$PWD/

# Configuration to use c++11
CONFIG += c++11
