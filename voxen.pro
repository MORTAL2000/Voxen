QT       += core gui  opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    source/glwidget.cpp \
    source/misc/SimplexNoise.cpp \
    source/misc/cinifile.cpp \
    source/misc/util.cpp \
    source/raytracer/camera.cpp \
    source/raytracer/material.cpp \
    source/raytracer/octtree.cpp \
    source/raytracer/ray.cpp \
    source/raytracer/raytracer.cpp \
    source/raytracer/raytracerglobals.cpp \
    source/renderer.cpp

HEADERS += \
    mainwindow.h \
    source/glwidget.h \
    source/misc/SimplexNoise.h \
    source/misc/cinifile.h \
    source/misc/random.h \
    source/misc/util.h \
    source/raytracer/camera.h \
    source/raytracer/material.h \
    source/raytracer/octtree.h \
    source/raytracer/ray.h \
    source/raytracer/raytracer.h \
    source/raytracer/raytracerglobals.h \
    source/renderer.h

FORMS += \
    mainwindow.ui


win32-msvc*{
    QMAKE_CXXFLAGS += -openmp
    LIBS += -openmp -opengl
    QMAKE_CXXFLAGS += -O3
    LIBS   += -lopengl32
    #LIBS   += -lglu32
    #LIBS   += -lglut32
#   QMAKE $$PWD\..\..\TRSE\Publish\tutorials\OK64\KOS\kos.prg $$PWD/resources/rom/

}
linux*{
    LIBS += -fopenmp
    QMAKE_CXXFLAGS += -fopenmp -O2

}



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    resources.qrc
