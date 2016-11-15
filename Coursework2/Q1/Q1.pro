# include various source .cpp files and header .h files in the build process
# (student's source code can be put into project root, or src/ subfolder)
SOURCES += $$PWD/lib/*.cpp
exists($$PWD/src/*.cpp) {
    SOURCES += $$PWD/src/*.cpp
}
exists($$PWD/src/test/*.cpp) {
    SOURCES += $$PWD/src/test/*.cpp
}
exists($$PWD/*.cpp) {
    SOURCES += $$PWD/*.cpp
}

HEADERS += $$PWD/lib*.h
exists($$PWD/src/*.h) {
    HEADERS += $$PWD/src/*.h
}
exists($$PWD/src/test/*.h) {
    HEADERS += $$PWD/src/test/*.h
}
exists($$PWD/*.h) {
    HEADERS += $$PWD/*.h
}
