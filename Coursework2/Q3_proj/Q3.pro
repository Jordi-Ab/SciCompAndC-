# This file specifies the information about your project to Qt Creator.
# You should not need to modify this file to complete your assignment.
#
# If you need to add files or folders to your project, we recommend the following:
# - close Qt Creator.
# - delete your ".pro.user" file and "build_xxxxxxx" directory.
# - place the new files/folders into your project directory.
# - re-open and "Configure" your project again.

# include various source .cpp files and header .h files in the build process
# (student's source code can be put into project root, or src/ subfolder)

# include various source .cpp files and header .h files in the build process
SOURCES += $$PWD/src/*.cpp

exists($$PWD/lib/*.cpp){
    SOURCES += $$PWD/lib/*.cpp
}
exists($$PWD/*.cpp) {
    SOURCES += $$PWD/*.cpp
}

exists($$PWD/lib/*.hpp){
    HEADERS += $$PWD/lib/*.hpp
}
exists($$PWD/src/*.h) {
    HEADERS += $$PWD/src/*.hpp
}

exists($$PWD/*.h) {
    HEADERS += $$PWD/*.hpp
}

# directories examined by Qt Creator when writing an #include statement
INCLUDEPATH += $$PWD/lib/
INCLUDEPATH += $$PWD/src/
INCLUDEPATH += $$PWD/

#Include c++11
CONFIG += c++11
