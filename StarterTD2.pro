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
SOURCES += main.cpp myglwidget.cpp \
    Car.cpp \
    Ground.cpp \
    barrel.cpp \
    fuelbar.cpp
HEADERS += myglwidget.h \
    Car.h \
    Ground.h \
    barrel.h \
    fuelbar.h

RESOURCES += \
    res/textures.qrc
