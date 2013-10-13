#-------------------------------------------------
#
# Project created by QtCreator 2012-06-12T02:29:18
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = TouchCar
TEMPLATE = app

INCLUDEPATH += /usr/local/include

SOURCES += main.cpp\
        mainwindow.cpp \
    qtipl.cpp \
    camera.cpp \
    light.cpp \
    turnsignal.cpp \
    stoplight.cpp \
    positionlight.cpp \
    mainbeam.cpp \
    lowbeam.cpp \
    backlight.cpp \
    opticalblock.cpp \
    frontopticalblock.cpp \
    frontleftopticalblock.cpp \
    frontrightopticalblock.cpp \
    rearopticalblock.cpp \
    rearleftopticalblock.cpp \
    rearrightopticalblock.cpp \
    canmessage.cpp \
    canmodul.cpp \
    car.cpp \
    controller.cpp \
    server.cpp \
    infos.cpp

HEADERS  += mainwindow.h \
    qtipl.h \
    camera.h \
    light.h \
    turnsignal.h \
    stoplight.h \
    positionlight.h \
    mainbeam.h \
    lowbeam.h \
    backlight.h \
    opticalblock.h \
    frontopticalblock.h \
    frontleftopticalblock.h \
    frontrightopticalblock.h \
    rearopticalblock.h \
    rearleftopticalblock.h \
    rearrightopticalblock.h \
    canmessage.h \
    canmodul.h \
    car.h \
    controller.h \
    server.h \
    infos.h

LIBS += -lm -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann
LIBS += -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml
LIBS += -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching
LIBS += -lopencv_ts -lopencv_video -lopencv_videostab

FORMS    += mainwindow.ui \
    infos.ui

RESOURCES += \
    ressources.qrc

ICON = ressources/logo/logo.icns
