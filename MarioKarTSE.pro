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
TARGET 	  = MarioKarTSE

# fichiers sources/headers/ressources
SOURCES += Main.cpp Widget.cpp \
    Car.cpp \
    Ground.cpp \
    Barrel.cpp \
    FuelBar.cpp \
    StopZone.cpp
HEADERS += Widget.h \
    Car.h \
    Ground.h \
    Barrel.h \
    FuelBar.h \
    StopZone.h

RESOURCES += \
    res/textures.qrc

    # ajout des libs au linker
INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include


LIBS     += -lopengl32 -lglu32 \
        -L$$(OPENCV_DIR)\lib \
        -lopencv_core451 \
        -lopencv_highgui451 \
        -lopencv_imgproc451 \
        -lopencv_imgcodecs451 \
        -lopencv_videoio451 \
        -lopencv_features2d451 \
        -lopencv_calib3d451 \
        -lopencv_objdetect451
