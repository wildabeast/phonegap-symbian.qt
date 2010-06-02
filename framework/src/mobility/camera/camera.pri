HEADERS += src/mobility/camera/xqcamera.h \
    src/mobility/camera/xqcamera_p.h \
    src/mobility/camera/xqviewfinderwidget.h \
    src/mobility/camera/xqviewfinderwidget_p.h
SOURCES += src/mobility/camera/xqviewfinderwidget.cpp \
    src/mobility/camera/xqviewfinderwidget_p.cpp \
    src/mobility/camera/xqcamera.cpp \
    src/mobility/camera/xqcamera_p.cpp
!exists($${EPOCROOT}epoc32/include/cameraengine.h):message("Warning: CameraEngine not found! Extract camerawrapper_epoc32.zip under epocroot.")
symbian:LIBS += -lcamerawrapper \
    -lfbscli
