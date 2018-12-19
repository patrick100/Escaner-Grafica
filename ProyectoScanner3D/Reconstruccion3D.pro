#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T11:05:44
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reconstruccion3D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    formopengl.cpp \
    glwidget.cpp \
    mlabel.cpp

HEADERS  += mainwindow.h \
    formopengl.h \
    glwidget.h \
    mlabel.h

FORMS    += mainwindow.ui \
    formopengl.ui

CONFIG += c++11

LIBS += -L/usr/local/lib -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core


LIBS += -lglut -lpthread -lX11
