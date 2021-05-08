# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app
CONFIG += c++17

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}


# nom de l'exe genere
TARGET 	  = StarterTD2

# fichiers sources/headers/ressources
SOURCES += Main.cpp Widget.cpp \
    Car.cpp \
    Ground.cpp \
    Barrel.cpp \
    FuelBar.cpp \
    stopzone.cpp
HEADERS += Widget.h \
    Car.h \
    Ground.h \
    Barrel.h \
    FuelBar.h \
    stopzone.h

RESOURCES += \
    res/textures.qrc
