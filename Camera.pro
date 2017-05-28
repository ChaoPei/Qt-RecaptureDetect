#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T10:50:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Camera
TEMPLATE = app

SOURCES += main.cpp\
        camerawidget.cpp

HEADERS  += camerawidget.h

FORMS += camerawidget.ui

# add Opencv include dir
INCLUDEPATH += "D:\opencv\build\include"\
               "D:\opencv\build\include\opencv"\
               "D:\opencv\build\include\opencv2"

# add Matlab include dir
INCLUDEPATH += "D:\Program Files\MATLAB\R2014a\extern\include"

# add Opencv libs dir
LIBS += -L"D:\opencv\build\x64\vc12\lib"

# add Matlab libs dir
LIBS += -L"D:\Program Files\MATLAB\R2014a\extern\lib\win64\microsoft"

# add Opencv libs
LIBS += -lopencv_calib3d2413d
LIBS += -lopencv_contrib2413d
LIBS += -lopencv_core2413d
LIBS += -lopencv_features2d2413d
LIBS += -lopencv_flann2413d
LIBS += -lopencv_gpu2413d
LIBS += -lopencv_highgui2413d
LIBS += -lopencv_imgproc2413d
LIBS += -lopencv_legacy2413d
LIBS += -lopencv_ml2413d
LIBS += -lopencv_nonfree2413d
LIBS += -lopencv_objdetect2413d
LIBS += -lopencv_ocl2413d
LIBS += -lopencv_photo2413d
LIBS += -lopencv_stitching2413d
LIBS += -lopencv_superres2413d
LIBS += -lopencv_ts2413d
LIBS += -lopencv_video2413d
LIBS += -lopencv_videostab2413d

# add Matlab libs
LIBS += -llibmat
LIBS += -llibmex
LIBS += -lmclmcr
LIBS += -lmclmcrrt

# add User self-define libs

LIBS += -L$$PWD

LIBS += -lRemake










