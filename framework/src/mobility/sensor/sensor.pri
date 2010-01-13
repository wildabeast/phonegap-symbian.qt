HEADERS += src/mobility/sensor/xqsensor.h \
    src/mobility/sensor/xqaccsensor.h \
    src/mobility/sensor/xqdeviceorientation.h \
    src/mobility/sensor/xqdeviceorientation_p.h

SOURCES += src/mobility/sensor/xqsensor.cpp \
    src/mobility/sensor/xqaccsensor.cpp \
    src/mobility/sensor/xqdeviceorientation.cpp \
    src/mobility/sensor/xqdeviceorientation_p.cpp

exists($${EPOCROOT}epoc32/release/winscw/udeb/SensrvClient.lib)| \
exists($${EPOCROOT}epoc32/release/armv5/lib/SensrvClient.lib) {
    message("Building for Sensor Framework")
    DEPENDPATH += .\framework

    HEADERS += src/mobility/sensor/framework/xqsensor_p.h \
        src/mobility/sensor/framework/xqaccsensor_p.h

    SOURCES += src/mobility/sensor/framework/xqsensor_p.cpp \
        src/mobility/sensor/framework/xqaccsensor_p.cpp

    symbian:TARGET.CAPABILITY += ReadDeviceData
    symbian:LIBS += -lSensrvClient \
        -lsensrvutil
} else {
    exists($${EPOCROOT}epoc32/release/winscw/udeb/RRSensorApi.lib)| \
    exists($${EPOCROOT}epoc32/release/armv5/lib/RRSensorApi.lib) {
        message( "Building for Sensor plugin" )

    DEPENDPATH += .\plugin

    HEADERS += src/mobility/sensor/framework/xqsensor_p.h \
        src/mobility/sensor/framework/xqaccsensor_p.h

    SOURCES += src/mobility/sensor/framework/xqsensor_p.cpp \
        src/mobility/sensor/framework/xqaccsensor_p.cpp

    symbian:LIBS += -lRRSensorApi
    } else {
        message("Warning: Sensor API not found!")

    }
}
