TEMPLATE = app
TARGET = PhoneGap
MOC_DIR = ./tmp
QT += core \
    gui \
    network \
    webkit \
    webkit
HEADERS += src/commands/Orientation.h \
    src/commands/Acceleration.h \
    src/commands/Camera.h \
    src/commands/Geolocation.h \
    src/BrowserView.h \
    src/BrowserWindow.h \
    src/CommandManager.h \
    src/commands/DebugConsole.h \
    src/commands/Notification.h
SOURCES += src/commands/Orientation.cpp \
    src/commands/Acceleration.cpp \
    src/commands/Camera.cpp \
    src/commands/Geolocation.cpp \
    src/BrowserView.cpp \
    src/BrowserWindow.cpp \
    src/CommandManager.cpp \
    src/Main.cpp \
    src/commands/DebugConsole.cpp \
    src/commands/Notification.cpp \
    PhoneGap_reg.rss
FORMS += 
RESOURCES += 
symbian { 
    TARGET.UID3 = 0xE666C00E
    ICON = src/icon.svg
    LIBS += -lesock \
        -linsock \
        -lconnmon \
        -lhwrmvibraclient
    TARGET.CAPABILITY = NetworkServices \
        Location \
        ReadUserData
    TARGET.EPOCHEAPSIZE = 0x20000 \
        0x2000000
    htmlfiles.sources = ./www
    htmlfiles.path = .
    DEPLOYMENT += htmlfiles
}
include(src/mobility/vibra/vibra.pri)
include(src/mobility/location/location.pri)
include(src/mobility/accesspointmanager/accesspointmanager.pri)
include(src/mobility/sensor/sensor.pri)
include(src/mobility/camera/camera.pri)

