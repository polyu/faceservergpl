#-------------------------------------------------
#
# Project created by QtCreator 2012-11-19T14:35:46
#
#-------------------------------------------------

QT       += core gui network

TARGET = FaceServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    verifier.cpp \
    utils.cpp \
    usermanager.cpp \
    faceDetector.cpp \
    eyesDetector.cpp \
    detector.cpp \
    tracker.cpp \
    webcamImagePaint.cpp

HEADERS  += mainwindow.h \
    verifier.h \
    utils.h \
    usermanager.h \
    faceDetector.h \
    eyesDetector.h \
    detector.h \
    tracker.h \
    webcamImagePaint.h

FORMS    += mainwindow.ui

LIBS+=  \
    /usr/lib/libopencv_core.so    \
    /usr/lib/libopencv_highgui.so \
    /usr/lib/libopencv_imgproc.so \
    /usr/lib/libopencv_objdetect.so \
